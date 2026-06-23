#pragma once

#include "domain.h"

class ClashDetector {
public:
    std::vector<Clash> detect(const Timetable& timetable) const;
};

class AnalyticsEngine {
public:
    AnalyticsSummary analyze(const std::vector<Faculty>& faculty,
                             const std::vector<Classroom>& rooms,
                             const std::vector<Batch>& batches,
                             const Timetable& timetable) const;
    int calculateStudentComfort(const std::vector<Batch>& batches, const Timetable& timetable) const;
};

class Scheduler {
    static bool roomMatches(const Classroom& room, const Subject& subject, const Batch& batch);
    static int slotWellnessPenalty(const Timetable& timetable, const Subject& subject, const Batch& batch, int day, int slot);
    static int dayLoad(const Timetable& timetable, const std::string& batchId, int day);
    static bool createsTheoryStreak(const Timetable& timetable, const Subject& subject, const std::string& batchId, int day, int slot);

public:
    Timetable generate(std::vector<Faculty>& faculty,
                       const std::vector<Subject>& subjects,
                       const std::vector<Classroom>& rooms,
                       const std::vector<Batch>& batches,
                       const std::vector<ScheduledClass>& fixedSlots = {}) const;
};
