#ifndef SMART_HOSPITAL_EMERGENCY_H
#define SMART_HOSPITAL_EMERGENCY_H

#include "hospital_base.h"

#include <queue>
#include <set>
#include <string>
#include <vector>

namespace smart_hospital {

struct EmergencyInfo {
    SeverityLevel severity;
    std::string emergencyType;
    int waitingTime;
};

class EmergencyCase : public Person {
private:
    EmergencyInfo info;
    int riskSnapshot;

public:
    EmergencyCase();
    EmergencyCase(std::string emergencyId, std::string patientName, int patientAge,
                  SeverityLevel severity, std::string type, int waitingTime);
    EmergencyCase(const EmergencyCase& other);
    ~EmergencyCase() override;

    SeverityLevel getSeverity() const;
    const std::string& getEmergencyType() const;
    int getWaitingTime() const;
    int getRiskSnapshot() const;
    int priorityScore() const;
    void setWaitingTime(int minutes);
    void setRiskSnapshot(int score);

    std::string generateReport() const override;
    void printSummary(std::ostream& out) const override;
    std::string serialize() const;
    static EmergencyCase deserialize(const std::string& line);
};

struct EmergencyComparator {
    bool operator()(const EmergencyCase& left, const EmergencyCase& right) const;
};

class EmergencyManager : public Reportable {
private:
    std::priority_queue<EmergencyCase, std::vector<EmergencyCase>, EmergencyComparator> triageQueue;
    std::vector<EmergencyCase> allCases;
    std::queue<std::string> triageNotes;
    std::set<std::string> activeEmergencyTypes;

public:
    static int totalEmergencies;

    EmergencyManager();
    ~EmergencyManager() override;

    void registerEmergency(const EmergencyCase& emergencyCase);
    bool hasPendingCases() const;
    EmergencyCase processNext();
    int predictWaitingTime(SeverityLevel severity) const;
    std::string resourceDashboardHint() const;

    const std::vector<EmergencyCase>& cases() const;
    std::string generateReport() const override;
    std::string generateStatistics() const;
    void saveToFile(const std::string& filePath) const;
    void loadFromFile(const std::string& filePath);
};

} // namespace smart_hospital

#endif
