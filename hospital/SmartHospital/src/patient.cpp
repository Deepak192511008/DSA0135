#include "patient.h"
#include "risk_analyzer.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace smart_hospital {

int Patient::patientCounter = 0;

std::string Patient::HistoryFormatter::format(const std::vector<VisitRecord>& visits) const {
    if (visits.empty()) {
        return "No visit history recorded.\n";
    }

    std::ostringstream out;
    int index = 1;
    for (const auto& visit : visits) {
        out << index++ << ". " << visit.date << " - " << visit.notes << '\n';
    }
    return out.str();
}

Patient::Patient()
    : Person(), diseaseSeverity(0), previousVisits(0), existingConditions(), history(),
      riskScore(0), riskCategory(RiskCategory::Low) {
    ++patientCounter;
}

Patient::Patient(std::string patientId, std::string patientName, int patientAge,
                 int severity, int visits)
    : Person(std::move(patientId), std::move(patientName), patientAge),
      diseaseSeverity(util::clampValue(severity, 0, 10)),
      previousVisits(std::max(0, visits)),
      existingConditions(),
      history(),
      riskScore(0),
      riskCategory(RiskCategory::Low) {
    ++patientCounter;
}

Patient::Patient(const Patient& other)
    : Person(other),
      diseaseSeverity(other.diseaseSeverity),
      previousVisits(other.previousVisits),
      existingConditions(other.existingConditions),
      history(other.history),
      riskScore(other.riskScore),
      riskCategory(other.riskCategory) {
    ++patientCounter;
}

Patient::~Patient() {
    --patientCounter;
}

void Patient::update(const std::string& patientName, int patientAge) {
    setName(patientName);
    setAge(patientAge);
}

void Patient::update(int severity, int visits) {
    diseaseSeverity = util::clampValue(severity, 0, 10);
    previousVisits = std::max(0, visits);
}

void Patient::update(const std::string& patientName, int patientAge, int severity, int visits) {
    update(patientName, patientAge);
    update(severity, visits);
}

void Patient::addCondition(const Condition& condition) {
    if (condition.name.empty()) {
        throw std::invalid_argument("Condition name cannot be empty.");
    }
    existingConditions.push_back({condition.name, util::clampValue(condition.severityImpact, 0, 25)});
}

void Patient::addVisit(const VisitRecord& visit) {
    if (visit.date.empty()) {
        throw std::invalid_argument("Visit date cannot be empty.");
    }
    history.push_back(visit);
    previousVisits = static_cast<int>(history.size());
}

int Patient::getDiseaseSeverity() const {
    return diseaseSeverity;
}

int Patient::getPreviousVisits() const {
    return previousVisits;
}

int Patient::getRiskScore() const {
    return riskScore;
}

RiskCategory Patient::getRiskCategory() const {
    return riskCategory;
}

const std::vector<Condition>& Patient::getConditions() const {
    return existingConditions;
}

const std::vector<VisitRecord>& Patient::getHistory() const {
    return history;
}

void Patient::setRisk(int score, RiskCategory category) {
    riskScore = util::clampValue(score, 0, 100);
    riskCategory = category;
}

std::string Patient::generateReport() const {
    static const char* categoryOrder[4] = {"Low", "Medium", "High", "Critical"};

    std::ostringstream out;
    out << "Patient Report\n"
        << "--------------\n"
        << Person::generateReport()
        << "Disease Severity: " << diseaseSeverity << "/10\n"
        << "Previous Visits: " << previousVisits << '\n'
        << "Risk Score: " << riskScore << '\n'
        << "Risk Category: " << toString(riskCategory) << '\n'
        << "Category Scale: ";

    for (const char* label : categoryOrder) {
        out << label << ' ';
    }
    out << "\nExisting Conditions:\n";

    if (existingConditions.empty()) {
        out << "- None\n";
    } else {
        for (const auto& condition : existingConditions) {
            out << "- " << condition.name << " (Impact " << condition.severityImpact << ")\n";
        }
    }

    out << "Visit History:\n" << HistoryFormatter().format(history);
    return out.str();
}

void Patient::printSummary(std::ostream& out) const {
    out << std::left << std::setw(12) << id
        << std::setw(22) << name
        << std::setw(6) << age
        << std::setw(10) << diseaseSeverity
        << std::setw(8) << riskScore
        << toString(riskCategory);
}

std::string Patient::serialize() const {
    std::vector<std::string> conditionParts;
    for (const auto& condition : existingConditions) {
        conditionParts.push_back(condition.name + "," + std::to_string(condition.severityImpact));
    }

    std::vector<std::string> historyParts;
    for (const auto& visit : history) {
        historyParts.push_back(visit.date + "," + visit.notes);
    }

    return util::join({
                          id,
                          name,
                          std::to_string(age),
                          std::to_string(riskScore),
                          toString(riskCategory),
                          std::to_string(diseaseSeverity),
                          std::to_string(previousVisits),
                          util::join(conditionParts, ';'),
                          util::join(historyParts, ';'),
                      },
                      '|');
}

std::shared_ptr<Patient> Patient::deserialize(const std::string& line) {
    const auto parts = util::split(line, '|');
    if (parts.size() < 5) {
        throw std::invalid_argument("Invalid patient record: " + line);
    }

    const int ageValue = util::toInt(parts[2], "Patient Age");
    const int scoreValue = util::toInt(parts[3], "Risk Score");
    const int severityValue = parts.size() > 5 ? util::toInt(parts[5], "Disease Severity") : 0;
    const int visitsValue = parts.size() > 6 ? util::toInt(parts[6], "Previous Visits") : 0;

    auto patient = std::make_shared<Patient>(parts[0], parts[1], ageValue, severityValue, visitsValue);
    patient->setRisk(scoreValue, riskCategoryFromString(parts[4]));

    if (parts.size() > 7 && !parts[7].empty()) {
        for (const auto& conditionText : util::split(parts[7], ';')) {
            const auto conditionParts = util::split(conditionText, ',');
            if (conditionParts.size() == 2) {
                patient->addCondition({conditionParts[0], util::toInt(conditionParts[1], "Condition Impact")});
            }
        }
    }

    if (parts.size() > 8 && !parts[8].empty()) {
        for (const auto& visitText : util::split(parts[8], ';')) {
            const auto visitParts = util::split(visitText, ',');
            if (visitParts.size() >= 2) {
                patient->history.push_back({visitParts[0], visitParts[1]});
            }
        }
        patient->previousVisits = std::max(patient->previousVisits, static_cast<int>(patient->history.size()));
    }

    return patient;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient) {
    patient.printSummary(out);
    return out;
}

PatientManager::PatientManager() = default;

PatientManager::~PatientManager() = default;

void PatientManager::addPatient(const std::shared_ptr<Patient>& patient) {
    if (!patient) {
        throw std::invalid_argument("Cannot add an empty patient.");
    }
    if (patients.findById(patient->getId())) {
        throw std::invalid_argument("Patient ID already exists.");
    }
    patients.add(patient);
}

std::shared_ptr<Patient> PatientManager::createPatient(const std::string& id, const std::string& name,
                                                       int age, int severity, int visits) {
    auto patient = std::make_shared<Patient>(id, name, age, severity, visits);
    addPatient(patient);
    return patient;
}

bool PatientManager::updatePatient(const std::string& id, const std::string& name, int age,
                                   int severity, int visits) {
    auto patient = patients.findById(id);
    if (!patient) {
        return false;
    }
    patient->update(name, age, severity, visits);
    patient->addVisit({util::currentDateTime(), "Patient profile updated"});
    return true;
}

bool PatientManager::deletePatient(const std::string& id) {
    return patients.removeById(id);
}

std::shared_ptr<Patient> PatientManager::searchPatient(const std::string& id) const {
    std::vector<std::string> ids;
    ids.reserve(patients.all().size());
    for (const auto& patient : patients.all()) {
        if (patient) {
            ids.push_back(patient->getId());
        }
    }
    std::sort(ids.begin(), ids.end());
    if (!std::binary_search(ids.begin(), ids.end(), id)) {
        return nullptr;
    }
    return patients.findById(id);
}

void PatientManager::analyzeAll(RiskAnalyzer& analyzer) {
    for (auto& patient : patients.all()) {
        if (patient) {
            analyzer.analyze(*patient);
        }
    }
}

const util::Repository<Patient>& PatientManager::getRepository() const {
    return patients;
}

util::Repository<Patient>& PatientManager::getRepository() {
    return patients;
}

std::string PatientManager::generateReport() const {
    std::ostringstream out;
    out << "Patient Management Report\n"
        << "=========================\n"
        << "Total Patients: " << patients.size() << "\n\n";

    auto sortedPatients = patients.all();
    std::sort(sortedPatients.begin(), sortedPatients.end(),
              [](const std::shared_ptr<Patient>& left, const std::shared_ptr<Patient>& right) {
                  return left->getRiskScore() > right->getRiskScore();
              });

    for (const auto& patient : sortedPatients) {
        if (patient) {
            out << patient->generateReport() << '\n';
        }
    }
    return out.str();
}

std::string PatientManager::generateRiskAnalysisReport() const {
    int* buckets = new int[4]{0, 0, 0, 0};

    for (const auto& patient : patients.all()) {
        if (!patient) {
            continue;
        }
        const int categoryIndex = static_cast<int>(patient->getRiskCategory());
        buckets[categoryIndex]++;
    }

    const int criticalCount = static_cast<int>(
        std::count_if(patients.all().begin(), patients.all().end(),
                      [](const std::shared_ptr<Patient>& patient) {
                          return patient && patient->getRiskCategory() == RiskCategory::Critical;
                      }));

    std::ostringstream out;
    out << "Risk Analysis Report\n"
        << "====================\n"
        << "Low Risk: " << buckets[0] << '\n'
        << "Medium Risk: " << buckets[1] << '\n'
        << "High Risk: " << buckets[2] << '\n'
        << "Critical Risk: " << buckets[3] << '\n'
        << "Critical Patients Requiring Immediate Review: " << criticalCount << '\n';

    delete[] buckets;
    return out.str();
}

void PatientManager::viewAll(std::ostream& out) const {
    out << std::left << std::setw(12) << "ID"
        << std::setw(22) << "Name"
        << std::setw(6) << "Age"
        << std::setw(10) << "Severity"
        << std::setw(8) << "Risk"
        << "Category\n";
    out << std::string(70, '-') << '\n';

    auto sortedPatients = patients.all();
    std::sort(sortedPatients.begin(), sortedPatients.end(),
              [](const std::shared_ptr<Patient>& left, const std::shared_ptr<Patient>& right) {
                  return left->getName() < right->getName();
              });

    for (const auto& patient : sortedPatients) {
        if (patient) {
            out << *patient << '\n';
        }
    }
}

void PatientManager::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open patient file for writing: " + filePath);
    }
    for (const auto& patient : patients.all()) {
        if (patient) {
            file << patient->serialize() << '\n';
        }
    }
}

void PatientManager::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open patient file for reading: " + filePath);
    }

    patients.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!util::trim(line).empty()) {
            patients.add(Patient::deserialize(line));
        }
    }
}

} // namespace smart_hospital
