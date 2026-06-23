#include "scheduler.h"

#include <limits>

namespace {
struct ScheduleTask {
    Batch batch;
    Subject subject;
};

bool isEdgeSlot(int slot)
{
    return slot == 0 || slot == Timetable::Slots - 1;
}
}

std::vector<Clash> ClashDetector::detect(const Timetable& timetable) const
{
    std::vector<Clash> clashes;
    std::map<std::string, int> facultyAtSlot;
    std::map<std::string, int> roomAtSlot;
    std::map<std::string, int> batchAtSlot;

    for (const auto& e : timetable.entries()) {
        if (e.breakSlot) {
            continue;
        }
        const std::string timeKey = std::to_string(e.day) + "-" + std::to_string(e.slot);
        if (++facultyAtSlot[e.facultyId + "@" + timeKey] > 1) {
            clashes.push_back({"Faculty conflict", e.facultyId + " has overlapping classes.", "Move one class to a free faculty slot."});
        }
        if (++roomAtSlot[e.roomNumber + "@" + timeKey] > 1) {
            clashes.push_back({"Room conflict", e.roomNumber + " is double booked.", "Assign another suitable room."});
        }
        if (++batchAtSlot[e.batchId + "@" + timeKey] > 1) {
            clashes.push_back({"Batch conflict", e.batchId + " has overlapping classes.", "Move the lowest priority subject to another slot."});
        }
    }
    return clashes;
}

AnalyticsSummary AnalyticsEngine::analyze(const std::vector<Faculty>& faculty,
                                          const std::vector<Classroom>& rooms,
                                          const std::vector<Batch>& batches,
                                          const Timetable& timetable) const
{
    AnalyticsSummary summary;
    const int roomCapacityHours = static_cast<int>(rooms.size()) * Timetable::Days * (Timetable::Slots - 1);
    int usedRoomHours = 0;

    for (const auto& e : timetable.entries()) {
        if (e.breakSlot) {
            continue;
        }
        ++usedRoomHours;
        summary.facultyHours[e.facultyId]++;
        summary.roomHours[e.roomNumber]++;
        summary.weeklyDistribution[Timetable::dayNames()[e.day]]++;
    }

    summary.classroomUtilization = roomCapacityHours == 0 ? 0.0 : (usedRoomHours * 100.0) / roomCapacityHours;

    double workloadTotal = 0.0;
    for (const auto& f : faculty) {
        const int hours = summary.facultyHours[f.id()];
        workloadTotal += f.maxHoursPerWeek() == 0 ? 0.0 : (hours * 100.0) / f.maxHoursPerWeek();
    }
    summary.averageFacultyWorkload = faculty.empty() ? 0.0 : workloadTotal / faculty.size();
    summary.studentComfortScore = calculateStudentComfort(batches, timetable);
    summary.totalClashes = static_cast<int>(ClashDetector().detect(timetable).size());
    return summary;
}

int AnalyticsEngine::calculateStudentComfort(const std::vector<Batch>& batches, const Timetable& timetable) const
{
    if (batches.empty()) {
        return 0;
    }

    int totalScore = 0;
    for (const auto& batch : batches) {
        int score = 100;
        for (int day = 0; day < Timetable::Days; ++day) {
            int classes = 0;
            int continuousTheory = 0;
            int gaps = 0;
            bool seenClass = false;
            bool hadGap = false;
            std::set<std::string> difficultSubjects;

            for (int slot = 0; slot < Timetable::Slots; ++slot) {
                const auto* e = timetable.findForBatch(batch.id(), day, slot);
                if (slot == Timetable::LunchSlot && (!e || !e->breakSlot)) {
                    score -= 5;
                }
                if (!e || e->breakSlot) {
                    if (seenClass && slot != Timetable::LunchSlot) {
                        hadGap = true;
                    }
                    continuousTheory = 0;
                    continue;
                }
                ++classes;
                if (hadGap) {
                    ++gaps;
                    hadGap = false;
                }
                seenClass = true;
                if (e->subjectType == SubjectType::Theory) {
                    ++continuousTheory;
                    if (continuousTheory > 3) {
                        score -= 8;
                    }
                } else {
                    continuousTheory = 0;
                }
                if (isEdgeSlot(slot)) {
                    score -= 2;
                }
                if (e->subjectName.find("Data") != std::string::npos || e->subjectName.find("Math") != std::string::npos) {
                    difficultSubjects.insert(e->subjectCode);
                }
            }
            if (classes == 1) {
                score -= 10;
            }
            score -= gaps * 3;
            if (difficultSubjects.size() > 2) {
                score -= 5;
            }
        }
        totalScore += std::max(0, std::min(100, score));
    }

    return totalScore / static_cast<int>(batches.size());
}

bool Scheduler::roomMatches(const Classroom& room, const Subject& subject, const Batch& batch)
{
    if (!room.available() || room.capacity() < batch.studentCount()) {
        return false;
    }
    return subject.type() == SubjectType::Lab ? room.type() == RoomType::Lab : true;
}

int Scheduler::dayLoad(const Timetable& timetable, const std::string& batchId, int day)
{
    int count = 0;
    for (const auto& e : timetable.entries()) {
        if (e.batchId == batchId && e.day == day && !e.breakSlot) {
            ++count;
        }
    }
    return count;
}

bool Scheduler::createsTheoryStreak(const Timetable& timetable, const Subject& subject, const std::string& batchId, int day, int slot)
{
    if (subject.type() != SubjectType::Theory) {
        return false;
    }
    int streak = 1;
    for (int s = slot - 1; s >= 0; --s) {
        const auto* e = timetable.findForBatch(batchId, day, s);
        if (!e || e->breakSlot || e->subjectType != SubjectType::Theory) {
            break;
        }
        ++streak;
    }
    for (int s = slot + 1; s < Timetable::Slots; ++s) {
        const auto* e = timetable.findForBatch(batchId, day, s);
        if (!e || e->breakSlot || e->subjectType != SubjectType::Theory) {
            break;
        }
        ++streak;
    }
    return streak > 3;
}

int Scheduler::slotWellnessPenalty(const Timetable& timetable, const Subject& subject, const Batch& batch, int day, int slot)
{
    int penalty = 0;
    penalty += dayLoad(timetable, batch.id(), day) * 2;
    if (isEdgeSlot(slot)) {
        penalty += 5;
    }
    if (createsTheoryStreak(timetable, subject, batch.id(), day, slot)) {
        penalty += 30;
    }
    if (subject.difficulty() >= 4 && slot >= 5) {
        penalty += 8;
    }
    if (slot == Timetable::LunchSlot) {
        penalty += 100;
    }
    return penalty;
}

Timetable Scheduler::generate(std::vector<Faculty>& faculty,
                              const std::vector<Subject>& subjects,
                              const std::vector<Classroom>& rooms,
                              const std::vector<Batch>& batches,
                              const std::vector<ScheduledClass>& fixedSlots) const
{
    Timetable timetable;
    for (auto& f : faculty) {
        f.setAssignedHours(0);
    }

    for (const auto& batch : batches) {
        for (int day = 0; day < Timetable::Days; ++day) {
            timetable.add({batch.id(), "BREAK", "Lunch Break", "", "", SubjectType::Theory, day, Timetable::LunchSlot, true, true});
        }
    }

    std::map<std::string, int> fixedCounts;
    for (auto fixed : fixedSlots) {
        if (fixed.slot == Timetable::LunchSlot || fixed.day < 0 || fixed.day >= Timetable::Days || fixed.slot < 0 || fixed.slot >= Timetable::Slots) {
            continue;
        }
        if (timetable.hasBatchClash(fixed.batchId, fixed.day, fixed.slot) ||
            timetable.hasFacultyClash(fixed.facultyId, fixed.day, fixed.slot) ||
            timetable.hasRoomClash(fixed.roomNumber, fixed.day, fixed.slot)) {
            continue;
        }
        fixed.fixed = true;
        timetable.add(fixed);
        fixedCounts[fixed.batchId + "@" + fixed.subjectCode]++;
        auto facultyIt = std::find_if(faculty.begin(), faculty.end(), [&](const Faculty& f) {
            return f.id() == fixed.facultyId;
        });
        if (facultyIt != faculty.end()) {
            facultyIt->setAssignedHours(facultyIt->assignedHours() + 1);
        }
    }

    std::vector<ScheduleTask> tasks;
    for (const auto& batch : batches) {
        for (const auto& subject : subjects) {
            const int remainingHours = std::max(0, subject.weeklyHours() - fixedCounts[batch.id() + "@" + subject.code()]);
            for (int i = 0; i < remainingHours; ++i) {
                tasks.push_back({batch, subject});
            }
        }
    }

    std::sort(tasks.begin(), tasks.end(), [](const ScheduleTask& a, const ScheduleTask& b) {
        if (a.subject.type() != b.subject.type()) {
            return a.subject.type() == SubjectType::Lab;
        }
        return a.subject.difficulty() > b.subject.difficulty();
    });

    for (const auto& task : tasks) {
        const auto facultyIt = std::find_if(faculty.begin(), faculty.end(), [&](const Faculty& f) {
            return f.id() == task.subject.assignedFacultyId();
        });
        if (facultyIt == faculty.end() || !facultyIt->canTakeMoreHours()) {
            continue;
        }

        int bestDay = -1;
        int bestSlot = -1;
        const Classroom* bestRoom = nullptr;
        int bestScore = std::numeric_limits<int>::max();

        for (int day = 0; day < Timetable::Days; ++day) {
            for (int slot = 0; slot < Timetable::Slots; ++slot) {
                if (slot == Timetable::LunchSlot || timetable.hasBatchClash(task.batch.id(), day, slot) ||
                    timetable.hasFacultyClash(task.subject.assignedFacultyId(), day, slot)) {
                    continue;
                }
                for (const auto& room : rooms) {
                    if (!roomMatches(room, task.subject, task.batch) || timetable.hasRoomClash(room.roomNumber(), day, slot)) {
                        continue;
                    }
                    const int capacityWaste = room.capacity() - task.batch.studentCount();
                    const int score = slotWellnessPenalty(timetable, task.subject, task.batch, day, slot) + capacityWaste;
                    if (score < bestScore) {
                        bestScore = score;
                        bestDay = day;
                        bestSlot = slot;
                        bestRoom = &room;
                    }
                }
            }
        }

        if (bestRoom) {
            timetable.add({task.batch.id(), task.subject.code(), task.subject.name(),
                           task.subject.assignedFacultyId(), bestRoom->roomNumber(), task.subject.type(),
                           bestDay, bestSlot, false, false});
            facultyIt->setAssignedHours(facultyIt->assignedHours() + 1);
        }
    }

    return timetable;
}
