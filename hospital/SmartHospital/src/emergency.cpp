#include "emergency.h"
#include "utility.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace smart_hospital {

int EmergencyManager::totalEmergencies = 0;

EmergencyCase::EmergencyCase()
    : Person(), info{SeverityLevel::Minor, "General", 0}, riskSnapshot(0) {}

EmergencyCase::EmergencyCase(std::string emergencyId, std::string patientName, int patientAge,
                             SeverityLevel severity, std::string type, int waitingTime)
    : Person(std::move(emergencyId), std::move(patientName), patientAge),
      info{severity, std::move(type), std::max(0, waitingTime)},
      riskSnapshot(0) {}

EmergencyCase::EmergencyCase(const EmergencyCase& other)
    : Person(other), info(other.info), riskSnapshot(other.riskSnapshot) {}

EmergencyCase::~EmergencyCase() = default;

SeverityLevel EmergencyCase::getSeverity() const {
    return info.severity;
}

const std::string& EmergencyCase::getEmergencyType() const {
    return info.emergencyType;
}

int EmergencyCase::getWaitingTime() const {
    return info.waitingTime;
}

int EmergencyCase::getRiskSnapshot() const {
    return riskSnapshot;
}

int EmergencyCase::priorityScore() const {
    return static_cast<int>(info.severity) * 100 + info.waitingTime + riskSnapshot / 5;
}

void EmergencyCase::setWaitingTime(int minutes) {
    info.waitingTime = std::max(0, minutes);
}

void EmergencyCase::setRiskSnapshot(int score) {
    riskSnapshot = util::clampValue(score, 0, 100);
}

std::string EmergencyCase::generateReport() const {
    std::ostringstream out;
    out << "Emergency ID: " << id << '\n'
        << "Patient: " << name << '\n'
        << "Age: " << age << '\n'
        << "Severity: " << toString(info.severity) << '\n'
        << "Emergency Type: " << info.emergencyType << '\n'
        << "Waiting Time: " << info.waitingTime << " minutes\n"
        << "Priority Score: " << priorityScore() << '\n';
    return out.str();
}

void EmergencyCase::printSummary(std::ostream& out) const {
    out << std::left << std::setw(12) << id
        << std::setw(20) << name
        << std::setw(12) << toString(info.severity)
        << std::setw(18) << info.emergencyType
        << std::setw(8) << info.waitingTime
        << priorityScore();
}

std::string EmergencyCase::serialize() const {
    return util::join({
                          id,
                          name,
                          std::to_string(age),
                          std::to_string(static_cast<int>(info.severity)),
                          info.emergencyType,
                          std::to_string(info.waitingTime),
                          std::to_string(riskSnapshot),
                      },
                      '|');
}

EmergencyCase EmergencyCase::deserialize(const std::string& line) {
    const auto parts = util::split(line, '|');
    if (parts.size() < 6) {
        throw std::invalid_argument("Invalid emergency record: " + line);
    }

    EmergencyCase emergency(parts[0],
                            parts[1],
                            util::toInt(parts[2], "Emergency Patient Age"),
                            severityFromInt(util::toInt(parts[3], "Emergency Severity")),
                            parts[4],
                            util::toInt(parts[5], "Waiting Time"));
    if (parts.size() > 6) {
        emergency.setRiskSnapshot(util::toInt(parts[6], "Risk Snapshot"));
    }
    return emergency;
}

bool EmergencyComparator::operator()(const EmergencyCase& left, const EmergencyCase& right) const {
    if (left.priorityScore() == right.priorityScore()) {
        return left.getWaitingTime() < right.getWaitingTime();
    }
    return left.priorityScore() < right.priorityScore();
}

EmergencyManager::EmergencyManager() = default;

EmergencyManager::~EmergencyManager() = default;

void EmergencyManager::registerEmergency(const EmergencyCase& emergencyCase) {
    allCases.push_back(emergencyCase);
    triageQueue.push(emergencyCase);
    triageNotes.push("Registered " + emergencyCase.getId() + " at " + util::currentDateTime());
    activeEmergencyTypes.insert(emergencyCase.getEmergencyType());
    ++totalEmergencies;
}

bool EmergencyManager::hasPendingCases() const {
    return !triageQueue.empty();
}

EmergencyCase EmergencyManager::processNext() {
    if (triageQueue.empty()) {
        throw std::runtime_error("No emergency cases are waiting.");
    }
    EmergencyCase next = triageQueue.top();
    triageQueue.pop();
    triageNotes.push("Processed " + next.getId() + " at " + util::currentDateTime());
    return next;
}

int EmergencyManager::predictWaitingTime(SeverityLevel severity) const {
    const int queueLoad = static_cast<int>(triageQueue.size()) * 7;
    const int severityOffset = (5 - static_cast<int>(severity)) * 6;
    return std::max(0, queueLoad + severityOffset);
}

std::string EmergencyManager::resourceDashboardHint() const {
    std::ostringstream out;
    out << "Emergency Load: " << triageQueue.size() << " pending cases, "
        << activeEmergencyTypes.size() << " active emergency types.";
    return out.str();
}

const std::vector<EmergencyCase>& EmergencyManager::cases() const {
    return allCases;
}

std::string EmergencyManager::generateReport() const {
    std::ostringstream out;
    out << "Emergency Report\n"
        << "================\n"
        << "Total Registered Emergencies: " << allCases.size() << '\n'
        << "Pending Queue Size: " << triageQueue.size() << '\n'
        << "Active Types: ";

    for (const auto& type : activeEmergencyTypes) {
        out << type << ' ';
    }
    out << "\n\n";

    auto sortedCases = allCases;
    std::sort(sortedCases.begin(), sortedCases.end(),
              [](const EmergencyCase& left, const EmergencyCase& right) {
                  return left.priorityScore() > right.priorityScore();
              });

    out << std::left << std::setw(12) << "ID"
        << std::setw(20) << "Patient"
        << std::setw(12) << "Severity"
        << std::setw(18) << "Type"
        << std::setw(8) << "Wait"
        << "Priority\n";
    out << std::string(82, '-') << '\n';

    for (const auto& emergency : sortedCases) {
        emergency.printSummary(out);
        out << '\n';
    }
    return out.str();
}

std::string EmergencyManager::generateStatistics() const {
    const int criticalCount = static_cast<int>(
        std::count_if(allCases.begin(), allCases.end(), [](const EmergencyCase& item) {
            return item.getSeverity() == SeverityLevel::Critical;
        }));

    const int severeOrHigher = static_cast<int>(
        std::count_if(allCases.begin(), allCases.end(), [](const EmergencyCase& item) {
            return static_cast<int>(item.getSeverity()) >= static_cast<int>(SeverityLevel::Severe);
        }));

    std::ostringstream out;
    out << "Emergency Statistics\n"
        << "====================\n"
        << "Total Cases: " << allCases.size() << '\n'
        << "Critical Cases: " << criticalCount << '\n'
        << "Severe or Higher: " << severeOrHigher << '\n'
        << "Predicted Wait for Critical Arrival: " << predictWaitingTime(SeverityLevel::Critical)
        << " minutes\n"
        << resourceDashboardHint() << '\n';
    return out.str();
}

void EmergencyManager::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open emergency file for writing: " + filePath);
    }
    for (const auto& emergency : allCases) {
        file << emergency.serialize() << '\n';
    }
}

void EmergencyManager::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open emergency file for reading: " + filePath);
    }

    allCases.clear();
    triageQueue = std::priority_queue<EmergencyCase, std::vector<EmergencyCase>, EmergencyComparator>();
    triageNotes = std::queue<std::string>();
    activeEmergencyTypes.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (util::trim(line).empty()) {
            continue;
        }
        EmergencyCase emergency = EmergencyCase::deserialize(line);
        allCases.push_back(emergency);
        triageQueue.push(emergency);
        activeEmergencyTypes.insert(emergency.getEmergencyType());
    }
    totalEmergencies = static_cast<int>(allCases.size());
}

} // namespace smart_hospital
