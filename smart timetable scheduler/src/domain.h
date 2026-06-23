#pragma once

#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class SubjectType { Theory, Lab };
enum class RoomType { Classroom, Lab };

std::string toString(SubjectType type);
std::string toString(RoomType type);
SubjectType subjectTypeFromString(const std::string& value);
RoomType roomTypeFromString(const std::string& value);

std::vector<std::string> splitList(const std::string& value, char delimiter = '|');
std::string joinList(const std::vector<std::string>& values, char delimiter = '|');

class Person {
protected:
    std::string id_;
    std::string name_;
    std::string department_;

public:
    Person() = default;
    Person(std::string id, std::string name, std::string department);
    virtual ~Person();

    const std::string& id() const;
    const std::string& name() const;
    const std::string& department() const;
    void setName(const std::string& name);
    void setDepartment(const std::string& department);

    virtual std::string role() const = 0;
};

class Faculty : public Person {
    std::vector<std::string> subjects_;
    int maxHoursPerWeek_ = 18;
    int leaveCount_ = 0;
    int assignedHours_ = 0;

public:
    Faculty() = default;
    Faculty(std::string id, std::string name, std::string department,
            std::vector<std::string> subjects, int maxHoursPerWeek, int leaveCount);
    ~Faculty() override;

    std::string role() const override;
    const std::vector<std::string>& subjects() const;
    int maxHoursPerWeek() const;
    int leaveCount() const;
    int assignedHours() const;
    void setSubjects(std::vector<std::string> subjects);
    void setMaxHoursPerWeek(int hours);
    void setLeaveCount(int leaves);
    void setAssignedHours(int hours);
    bool canTakeMoreHours(int additional = 1) const;
};

class Subject {
    std::string code_;
    std::string name_;
    int weeklyHours_ = 3;
    SubjectType type_ = SubjectType::Theory;
    std::string assignedFacultyId_;
    int difficulty_ = 2;

public:
    Subject() = default;
    Subject(std::string code, std::string name, int weeklyHours, SubjectType type,
            std::string assignedFacultyId, int difficulty = 2);

    const std::string& code() const;
    const std::string& name() const;
    int weeklyHours() const;
    SubjectType type() const;
    const std::string& assignedFacultyId() const;
    int difficulty() const;
    void setName(const std::string& name);
    void setWeeklyHours(int hours);
    void setType(SubjectType type);
    void setAssignedFacultyId(const std::string& facultyId);
    void setDifficulty(int difficulty);
};

class Classroom {
    std::string roomNumber_;
    int capacity_ = 60;
    RoomType type_ = RoomType::Classroom;
    bool available_ = true;

public:
    Classroom() = default;
    Classroom(std::string roomNumber, int capacity, RoomType type, bool available);

    const std::string& roomNumber() const;
    int capacity() const;
    RoomType type() const;
    bool available() const;
    void setCapacity(int capacity);
    void setType(RoomType type);
    void setAvailable(bool available);
};

class Batch {
    std::string id_;
    int semester_ = 1;
    std::string section_;
    int studentCount_ = 60;

public:
    Batch() = default;
    Batch(std::string id, int semester, std::string section, int studentCount);

    const std::string& id() const;
    int semester() const;
    const std::string& section() const;
    int studentCount() const;
    void setSemester(int semester);
    void setSection(const std::string& section);
    void setStudentCount(int count);
};

struct ScheduledClass {
    std::string batchId;
    std::string subjectCode;
    std::string subjectName;
    std::string facultyId;
    std::string roomNumber;
    SubjectType subjectType = SubjectType::Theory;
    int day = 0;
    int slot = 0;
    bool fixed = false;
    bool breakSlot = false;
};

struct Clash {
    std::string type;
    std::string message;
    std::string suggestion;
};

class Timetable {
    std::vector<ScheduledClass> entries_;

public:
    static constexpr int Days = 6;
    static constexpr int Slots = 8;
    static constexpr int LunchSlot = 3;

    static const std::vector<std::string>& dayNames();
    static const std::vector<std::string>& slotNames();

    void clear();
    void add(const ScheduledClass& entry);
    const std::vector<ScheduledClass>& entries() const;
    std::vector<ScheduledClass> entriesForBatch(const std::string& batchId) const;
    std::vector<ScheduledClass> entriesForFaculty(const std::string& facultyId) const;
    std::vector<ScheduledClass> entriesForRoom(const std::string& roomNumber) const;
    const ScheduledClass* findForBatch(const std::string& batchId, int day, int slot) const;
    bool hasFacultyClash(const std::string& facultyId, int day, int slot) const;
    bool hasRoomClash(const std::string& roomNumber, int day, int slot) const;
    bool hasBatchClash(const std::string& batchId, int day, int slot) const;
};

struct AnalyticsSummary {
    double classroomUtilization = 0.0;
    double averageFacultyWorkload = 0.0;
    int studentComfortScore = 0;
    int totalClashes = 0;
    std::map<std::string, int> facultyHours;
    std::map<std::string, int> roomHours;
    std::map<std::string, int> weeklyDistribution;
};

template <typename T>
const T* findById(const std::vector<T>& items, const std::string& id)
{
    auto it = std::find_if(items.begin(), items.end(), [&](const T& item) { return item.id() == id; });
    return it == items.end() ? nullptr : &(*it);
}

template <>
inline const Subject* findById<Subject>(const std::vector<Subject>& items, const std::string& id)
{
    auto it = std::find_if(items.begin(), items.end(), [&](const Subject& item) { return item.code() == id; });
    return it == items.end() ? nullptr : &(*it);
}

template <>
inline const Classroom* findById<Classroom>(const std::vector<Classroom>& items, const std::string& id)
{
    auto it = std::find_if(items.begin(), items.end(), [&](const Classroom& item) { return item.roomNumber() == id; });
    return it == items.end() ? nullptr : &(*it);
}

