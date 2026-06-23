#pragma once

#include "domain.h"

#include <fstream>

struct AppData {
    std::vector<Faculty> faculty;
    std::vector<Subject> subjects;
    std::vector<Classroom> rooms;
    std::vector<Batch> batches;
    std::vector<ScheduledClass> fixedSlots;
    Timetable timetable;
};

class CsvRepository {
    std::string dataDir_;

    static std::vector<std::string> parseCsvLine(const std::string& line);

public:
    explicit CsvRepository(std::string dataDir);
    static std::string escapeCsv(const std::string& value);

    AppData loadAll();
    void saveAll(const AppData& data);
    void saveTimetable(const Timetable& timetable);
    bool validatePassword(const std::string& password) const;
    void changePassword(const std::string& oldPassword, const std::string& newPassword);
    void ensureSampleData();
};

class ReportManager {
    std::string reportDir_;

public:
    explicit ReportManager(std::string reportDir);

    void exportTimetableCsv(const Timetable& timetable, const std::string& fileName = "timetable_export.csv") const;
    void exportTimetableTxt(const Timetable& timetable, const std::string& fileName = "timetable_report.txt") const;
    void exportFacultyReport(const std::vector<Faculty>& faculty, const Timetable& timetable) const;
    void exportClassroomReport(const std::vector<Classroom>& rooms, const Timetable& timetable) const;
    void exportStudentComfortReport(int comfortScore, const std::vector<Clash>& clashes) const;
};
