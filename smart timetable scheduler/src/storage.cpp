#include "storage.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QDir>
#include <QString>

#include <iomanip>

namespace {
std::string joinPath(const std::string& dir, const std::string& file)
{
    return dir + "/" + file;
}

bool fileExists(const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}

std::string hashPassword(const std::string& password)
{
    const QByteArray salted = QByteArray("smart-classroom:") + QByteArray::fromStdString(password);
    return "sha256:" + QCryptographicHash::hash(salted, QCryptographicHash::Sha256).toHex().toStdString();
}

void requireFile(std::ofstream& file, const std::string& path)
{
    if (!file) {
        throw std::runtime_error("Unable to write file: " + path);
    }
}

void requireFile(std::ifstream& file, const std::string& path)
{
    if (!file) {
        throw std::runtime_error("Unable to read file: " + path);
    }
}
}

CsvRepository::CsvRepository(std::string dataDir) : dataDir_(std::move(dataDir))
{
    QDir().mkpath(QString::fromStdString(dataDir_));
}

std::vector<std::string> CsvRepository::parseCsvLine(const std::string& line)
{
    std::vector<std::string> values;
    std::string current;
    bool quoted = false;
    for (char ch : line) {
        if (ch == '"') {
            quoted = !quoted;
        } else if (ch == ',' && !quoted) {
            values.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    values.push_back(current);
    return values;
}

std::string CsvRepository::escapeCsv(const std::string& value)
{
    if (value.find_first_of(",\"") == std::string::npos) {
        return value;
    }
    std::string escaped = "\"";
    for (char ch : value) {
        if (ch == '"') {
            escaped += "\"\"";
        } else {
            escaped += ch;
        }
    }
    escaped += "\"";
    return escaped;
}

AppData CsvRepository::loadAll()
{
    ensureSampleData();
    AppData data;

    {
        const auto path = joinPath(dataDir_, "faculty.csv");
        std::ifstream file(path);
        requireFile(file, path);
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            auto cols = parseCsvLine(line);
            if (cols.size() >= 6) {
                data.faculty.emplace_back(cols[0], cols[1], cols[2], splitList(cols[3]), std::stoi(cols[4]), std::stoi(cols[5]));
            }
        }
    }

    {
        const auto path = joinPath(dataDir_, "subjects.csv");
        std::ifstream file(path);
        requireFile(file, path);
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            auto cols = parseCsvLine(line);
            if (cols.size() >= 6) {
                data.subjects.emplace_back(cols[0], cols[1], std::stoi(cols[2]), subjectTypeFromString(cols[3]), cols[4], std::stoi(cols[5]));
            }
        }
    }

    {
        const auto path = joinPath(dataDir_, "rooms.csv");
        std::ifstream file(path);
        requireFile(file, path);
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            auto cols = parseCsvLine(line);
            if (cols.size() >= 4) {
                data.rooms.emplace_back(cols[0], std::stoi(cols[1]), roomTypeFromString(cols[2]), cols[3] == "1");
            }
        }
    }

    {
        const auto path = joinPath(dataDir_, "batches.csv");
        std::ifstream file(path);
        requireFile(file, path);
        std::string line;
        std::getline(file, line);
        while (std::getline(file, line)) {
            auto cols = parseCsvLine(line);
            if (cols.size() >= 4) {
                data.batches.emplace_back(cols[0], std::stoi(cols[1]), cols[2], std::stoi(cols[3]));
            }
        }
    }

    {
        const auto path = joinPath(dataDir_, "fixed_slots.csv");
        std::ifstream file(path);
        if (file) {
            std::string line;
            std::getline(file, line);
            while (std::getline(file, line)) {
                auto cols = parseCsvLine(line);
                if (cols.size() >= 6) {
                    const Subject* subject = findById(data.subjects, cols[3]);
                    data.fixedSlots.push_back({cols[0],
                                               cols[3],
                                               subject ? subject->name() : cols[3],
                                               cols[4],
                                               cols[5],
                                               subject ? subject->type() : SubjectType::Theory,
                                               std::stoi(cols[1]),
                                               std::stoi(cols[2]),
                                               true,
                                               false});
                }
            }
        }
    }

    return data;
}

void CsvRepository::saveAll(const AppData& data)
{
    QDir().mkpath(QString::fromStdString(dataDir_));
    {
        const auto path = joinPath(dataDir_, "faculty.csv");
        std::ofstream file(path);
        requireFile(file, path);
        file << "id,name,department,subjects,max_hours,leave_count\n";
        for (const auto& f : data.faculty) {
            file << f.id() << ',' << escapeCsv(f.name()) << ',' << escapeCsv(f.department()) << ','
                 << escapeCsv(joinList(f.subjects())) << ',' << f.maxHoursPerWeek() << ',' << f.leaveCount() << '\n';
        }
    }
    {
        const auto path = joinPath(dataDir_, "subjects.csv");
        std::ofstream file(path);
        requireFile(file, path);
        file << "code,name,weekly_hours,type,faculty_id,difficulty\n";
        for (const auto& s : data.subjects) {
            file << s.code() << ',' << escapeCsv(s.name()) << ',' << s.weeklyHours() << ','
                 << toString(s.type()) << ',' << s.assignedFacultyId() << ',' << s.difficulty() << '\n';
        }
    }
    {
        const auto path = joinPath(dataDir_, "rooms.csv");
        std::ofstream file(path);
        requireFile(file, path);
        file << "room,capacity,type,available\n";
        for (const auto& r : data.rooms) {
            file << r.roomNumber() << ',' << r.capacity() << ',' << toString(r.type()) << ',' << (r.available() ? 1 : 0) << '\n';
        }
    }
    {
        const auto path = joinPath(dataDir_, "batches.csv");
        std::ofstream file(path);
        requireFile(file, path);
        file << "id,semester,section,student_count\n";
        for (const auto& b : data.batches) {
            file << b.id() << ',' << b.semester() << ',' << escapeCsv(b.section()) << ',' << b.studentCount() << '\n';
        }
    }
    {
        const auto path = joinPath(dataDir_, "fixed_slots.csv");
        std::ofstream file(path);
        requireFile(file, path);
        file << "batch,day,slot,subject_code,faculty_id,room\n";
        for (const auto& e : data.fixedSlots) {
            file << e.batchId << ',' << e.day << ',' << e.slot << ',' << e.subjectCode << ',' << e.facultyId << ',' << e.roomNumber << '\n';
        }
    }
    saveTimetable(data.timetable);
}

void CsvRepository::saveTimetable(const Timetable& timetable)
{
    const auto path = joinPath(dataDir_, "timetable.csv");
    std::ofstream file(path);
    requireFile(file, path);
    file << "batch,day,slot,subject_code,subject_name,faculty,room,type,fixed,break\n";
    for (const auto& e : timetable.entries()) {
        file << e.batchId << ',' << e.day << ',' << e.slot << ',' << e.subjectCode << ','
             << escapeCsv(e.subjectName) << ',' << e.facultyId << ',' << e.roomNumber << ','
             << toString(e.subjectType) << ',' << (e.fixed ? 1 : 0) << ',' << (e.breakSlot ? 1 : 0) << '\n';
    }
}

bool CsvRepository::validatePassword(const std::string& password) const
{
    const auto path = joinPath(dataDir_, "admin.txt");
    std::ifstream file(path);
    if (!file) {
        return password == "admin123";
    }
    std::string stored;
    std::getline(file, stored);
    if (stored.rfind("sha256:", 0) == 0) {
        return stored == hashPassword(password);
    }
    return stored == password;
}

void CsvRepository::changePassword(const std::string& oldPassword, const std::string& newPassword)
{
    if (!validatePassword(oldPassword)) {
        throw std::runtime_error("Old password is incorrect.");
    }
    if (newPassword.size() < 6) {
        throw std::runtime_error("Password must contain at least 6 characters.");
    }
    const auto path = joinPath(dataDir_, "admin.txt");
    std::ofstream file(path);
    requireFile(file, path);
    file << hashPassword(newPassword);
}

void CsvRepository::ensureSampleData()
{
    QDir().mkpath(QString::fromStdString(dataDir_));
    if (!fileExists(joinPath(dataDir_, "admin.txt"))) {
        std::ofstream(joinPath(dataDir_, "admin.txt")) << hashPassword("admin123");
    }
    if (!fileExists(joinPath(dataDir_, "faculty.csv"))) {
        std::ofstream file(joinPath(dataDir_, "faculty.csv"));
        file << "id,name,department,subjects,max_hours,leave_count\n"
             << "F001,Dr. Meera Sharma,CSE,CS101|CS104,18,1\n"
             << "F002,Prof. Arjun Rao,CSE,CS102|CS105,16,0\n"
             << "F003,Dr. Kavita Menon,ECE,CS103|CS106,15,2\n"
             << "F004,Prof. Imran Khan,Mathematics,MA101,14,0\n";
    }
    if (!fileExists(joinPath(dataDir_, "subjects.csv"))) {
        std::ofstream file(joinPath(dataDir_, "subjects.csv"));
        file << "code,name,weekly_hours,type,faculty_id,difficulty\n"
             << "CS101,Data Structures,4,Theory,F001,5\n"
             << "CS102,Database Systems,4,Theory,F002,4\n"
             << "CS103,Digital Electronics,3,Theory,F003,3\n"
             << "CS104,Data Structures Lab,2,Lab,F001,4\n"
             << "CS105,Database Lab,2,Lab,F002,4\n"
             << "MA101,Discrete Mathematics,4,Theory,F004,5\n";
    }
    if (!fileExists(joinPath(dataDir_, "rooms.csv"))) {
        std::ofstream file(joinPath(dataDir_, "rooms.csv"));
        file << "room,capacity,type,available\n"
             << "A-101,70,Classroom,1\n"
             << "A-102,60,Classroom,1\n"
             << "Lab-1,70,Lab,1\n"
             << "Lab-2,70,Lab,1\n";
    }
    if (!fileExists(joinPath(dataDir_, "batches.csv"))) {
        std::ofstream file(joinPath(dataDir_, "batches.csv"));
        file << "id,semester,section,student_count\n"
             << "CSE-S3-A,3,A,58\n"
             << "CSE-S3-B,3,B,55\n";
    }
    if (!fileExists(joinPath(dataDir_, "fixed_slots.csv"))) {
        std::ofstream file(joinPath(dataDir_, "fixed_slots.csv"));
        file << "batch,day,slot,subject_code,faculty_id,room\n"
             << "CSE-S3-A,0,0,MA101,F004,A-101\n";
    }
}

ReportManager::ReportManager(std::string reportDir) : reportDir_(std::move(reportDir))
{
    QDir().mkpath(QString::fromStdString(reportDir_));
}

void ReportManager::exportTimetableCsv(const Timetable& timetable, const std::string& fileName) const
{
    const auto path = joinPath(reportDir_, fileName);
    std::ofstream file(path);
    requireFile(file, path);
    file << "Batch,Day,Time,Subject,Faculty,Room,Type\n";
    for (const auto& e : timetable.entries()) {
        file << e.batchId << ',' << Timetable::dayNames()[e.day] << ',' << Timetable::slotNames()[e.slot] << ','
             << CsvRepository::escapeCsv(e.breakSlot ? "Lunch Break" : e.subjectName) << ','
             << e.facultyId << ',' << e.roomNumber << ',' << (e.breakSlot ? "Break" : toString(e.subjectType)) << '\n';
    }
}

void ReportManager::exportTimetableTxt(const Timetable& timetable, const std::string& fileName) const
{
    const auto path = joinPath(reportDir_, fileName);
    std::ofstream file(path);
    requireFile(file, path);
    file << "Smart Classroom Timetable Report\n\n";
    for (const auto& e : timetable.entries()) {
        file << e.batchId << " | " << Timetable::dayNames()[e.day] << " | " << Timetable::slotNames()[e.slot] << " | "
             << (e.breakSlot ? "Lunch Break" : e.subjectName) << " | " << e.facultyId << " | " << e.roomNumber << '\n';
    }
}

void ReportManager::exportFacultyReport(const std::vector<Faculty>& faculty, const Timetable& timetable) const
{
    const auto path = joinPath(reportDir_, "faculty_workload_report.txt");
    std::ofstream file(path);
    requireFile(file, path);
    file << "Faculty Workload Report\n\n";
    for (const auto& f : faculty) {
        const int hours = static_cast<int>(timetable.entriesForFaculty(f.id()).size());
        file << f.id() << " - " << f.name() << ": " << hours << "/" << f.maxHoursPerWeek() << " hours, leaves "
             << f.leaveCount() << '\n';
    }
}

void ReportManager::exportClassroomReport(const std::vector<Classroom>& rooms, const Timetable& timetable) const
{
    const auto path = joinPath(reportDir_, "classroom_utilization_report.txt");
    std::ofstream file(path);
    requireFile(file, path);
    file << "Classroom Utilization Report\n\n";
    for (const auto& room : rooms) {
        const int hours = static_cast<int>(timetable.entriesForRoom(room.roomNumber()).size());
        file << room.roomNumber() << " (" << toString(room.type()) << "): " << hours << " scheduled hours\n";
    }
}

void ReportManager::exportStudentComfortReport(int comfortScore, const std::vector<Clash>& clashes) const
{
    const auto path = joinPath(reportDir_, "student_comfort_report.txt");
    std::ofstream file(path);
    requireFile(file, path);
    file << "Student Wellness Optimization Report\n\n";
    file << "Comfort Score: " << comfortScore << "/100\n\n";
    file << "Detected Issues and Suggestions\n";
    for (const auto& clash : clashes) {
        file << "- " << clash.type << ": " << clash.message << " Suggestion: " << clash.suggestion << '\n';
    }
}
