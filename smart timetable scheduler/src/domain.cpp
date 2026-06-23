#include "domain.h"

namespace {
std::string trim(const std::string& value)
{
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}
}

std::string toString(SubjectType type)
{
    return type == SubjectType::Lab ? "Lab" : "Theory";
}

std::string toString(RoomType type)
{
    return type == RoomType::Lab ? "Lab" : "Classroom";
}

SubjectType subjectTypeFromString(const std::string& value)
{
    const std::string normalized = trim(value);
    return normalized == "Lab" || normalized == "lab" ? SubjectType::Lab : SubjectType::Theory;
}

RoomType roomTypeFromString(const std::string& value)
{
    const std::string normalized = trim(value);
    return normalized == "Lab" || normalized == "lab" ? RoomType::Lab : RoomType::Classroom;
}

std::vector<std::string> splitList(const std::string& value, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(value);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        token = trim(token);
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}

std::string joinList(const std::vector<std::string>& values, char delimiter)
{
    std::ostringstream out;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            out << delimiter;
        }
        out << values[i];
    }
    return out.str();
}

Person::Person(std::string id, std::string name, std::string department)
    : id_(std::move(id)), name_(std::move(name)), department_(std::move(department))
{
}

Person::~Person() = default;

const std::string& Person::id() const { return id_; }
const std::string& Person::name() const { return name_; }
const std::string& Person::department() const { return department_; }
void Person::setName(const std::string& name) { name_ = name; }
void Person::setDepartment(const std::string& department) { department_ = department; }

Faculty::Faculty(std::string id, std::string name, std::string department,
                 std::vector<std::string> subjects, int maxHoursPerWeek, int leaveCount)
    : Person(std::move(id), std::move(name), std::move(department)),
      subjects_(std::move(subjects)),
      maxHoursPerWeek_(maxHoursPerWeek),
      leaveCount_(leaveCount)
{
}

Faculty::~Faculty() = default;

std::string Faculty::role() const { return "Faculty"; }
const std::vector<std::string>& Faculty::subjects() const { return subjects_; }
int Faculty::maxHoursPerWeek() const { return maxHoursPerWeek_; }
int Faculty::leaveCount() const { return leaveCount_; }
int Faculty::assignedHours() const { return assignedHours_; }
void Faculty::setSubjects(std::vector<std::string> subjects) { subjects_ = std::move(subjects); }
void Faculty::setMaxHoursPerWeek(int hours) { maxHoursPerWeek_ = hours; }
void Faculty::setLeaveCount(int leaves) { leaveCount_ = leaves; }
void Faculty::setAssignedHours(int hours) { assignedHours_ = hours; }
bool Faculty::canTakeMoreHours(int additional) const { return assignedHours_ + additional <= maxHoursPerWeek_; }

Subject::Subject(std::string code, std::string name, int weeklyHours, SubjectType type,
                 std::string assignedFacultyId, int difficulty)
    : code_(std::move(code)),
      name_(std::move(name)),
      weeklyHours_(weeklyHours),
      type_(type),
      assignedFacultyId_(std::move(assignedFacultyId)),
      difficulty_(difficulty)
{
}

const std::string& Subject::code() const { return code_; }
const std::string& Subject::name() const { return name_; }
int Subject::weeklyHours() const { return weeklyHours_; }
SubjectType Subject::type() const { return type_; }
const std::string& Subject::assignedFacultyId() const { return assignedFacultyId_; }
int Subject::difficulty() const { return difficulty_; }
void Subject::setName(const std::string& name) { name_ = name; }
void Subject::setWeeklyHours(int hours) { weeklyHours_ = hours; }
void Subject::setType(SubjectType type) { type_ = type; }
void Subject::setAssignedFacultyId(const std::string& facultyId) { assignedFacultyId_ = facultyId; }
void Subject::setDifficulty(int difficulty) { difficulty_ = std::max(1, std::min(5, difficulty)); }

Classroom::Classroom(std::string roomNumber, int capacity, RoomType type, bool available)
    : roomNumber_(std::move(roomNumber)), capacity_(capacity), type_(type), available_(available)
{
}

const std::string& Classroom::roomNumber() const { return roomNumber_; }
int Classroom::capacity() const { return capacity_; }
RoomType Classroom::type() const { return type_; }
bool Classroom::available() const { return available_; }
void Classroom::setCapacity(int capacity) { capacity_ = capacity; }
void Classroom::setType(RoomType type) { type_ = type; }
void Classroom::setAvailable(bool available) { available_ = available; }

Batch::Batch(std::string id, int semester, std::string section, int studentCount)
    : id_(std::move(id)), semester_(semester), section_(std::move(section)), studentCount_(studentCount)
{
}

const std::string& Batch::id() const { return id_; }
int Batch::semester() const { return semester_; }
const std::string& Batch::section() const { return section_; }
int Batch::studentCount() const { return studentCount_; }
void Batch::setSemester(int semester) { semester_ = semester; }
void Batch::setSection(const std::string& section) { section_ = section; }
void Batch::setStudentCount(int count) { studentCount_ = count; }

const std::vector<std::string>& Timetable::dayNames()
{
    static const std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days;
}

const std::vector<std::string>& Timetable::slotNames()
{
    static const std::vector<std::string> slots = {
        "09:00-10:00", "10:00-11:00", "11:00-12:00", "12:00-01:00",
        "01:00-02:00", "02:00-03:00", "03:00-04:00", "04:00-05:00"};
    return slots;
}

void Timetable::clear() { entries_.clear(); }
void Timetable::add(const ScheduledClass& entry) { entries_.push_back(entry); }
const std::vector<ScheduledClass>& Timetable::entries() const { return entries_; }

std::vector<ScheduledClass> Timetable::entriesForBatch(const std::string& batchId) const
{
    std::vector<ScheduledClass> result;
    std::copy_if(entries_.begin(), entries_.end(), std::back_inserter(result),
                 [&](const ScheduledClass& entry) { return entry.batchId == batchId; });
    return result;
}

std::vector<ScheduledClass> Timetable::entriesForFaculty(const std::string& facultyId) const
{
    std::vector<ScheduledClass> result;
    std::copy_if(entries_.begin(), entries_.end(), std::back_inserter(result),
                 [&](const ScheduledClass& entry) { return entry.facultyId == facultyId && !entry.breakSlot; });
    return result;
}

std::vector<ScheduledClass> Timetable::entriesForRoom(const std::string& roomNumber) const
{
    std::vector<ScheduledClass> result;
    std::copy_if(entries_.begin(), entries_.end(), std::back_inserter(result),
                 [&](const ScheduledClass& entry) { return entry.roomNumber == roomNumber && !entry.breakSlot; });
    return result;
}

const ScheduledClass* Timetable::findForBatch(const std::string& batchId, int day, int slot) const
{
    auto it = std::find_if(entries_.begin(), entries_.end(), [&](const ScheduledClass& entry) {
        return entry.batchId == batchId && entry.day == day && entry.slot == slot;
    });
    return it == entries_.end() ? nullptr : &(*it);
}

bool Timetable::hasFacultyClash(const std::string& facultyId, int day, int slot) const
{
    return std::any_of(entries_.begin(), entries_.end(), [&](const ScheduledClass& entry) {
        return !entry.breakSlot && entry.facultyId == facultyId && entry.day == day && entry.slot == slot;
    });
}

bool Timetable::hasRoomClash(const std::string& roomNumber, int day, int slot) const
{
    return std::any_of(entries_.begin(), entries_.end(), [&](const ScheduledClass& entry) {
        return !entry.breakSlot && entry.roomNumber == roomNumber && entry.day == day && entry.slot == slot;
    });
}

bool Timetable::hasBatchClash(const std::string& batchId, int day, int slot) const
{
    return std::any_of(entries_.begin(), entries_.end(), [&](const ScheduledClass& entry) {
        return entry.batchId == batchId && entry.day == day && entry.slot == slot;
    });
}

