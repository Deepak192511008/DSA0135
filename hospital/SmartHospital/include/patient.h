#ifndef SMART_HOSPITAL_PATIENT_H
#define SMART_HOSPITAL_PATIENT_H

#include "hospital_base.h"
#include "utility.h"

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

namespace smart_hospital {

struct Condition {
    std::string name;
    int severityImpact;
};

struct VisitRecord {
    std::string date;
    std::string notes;
};

class RiskAnalyzer;

class Patient : public Person {
private:
    int diseaseSeverity;
    int previousVisits;
    std::vector<Condition> existingConditions;
    std::vector<VisitRecord> history;
    int riskScore;
    RiskCategory riskCategory;

public:
    class HistoryFormatter {
    public:
        std::string format(const std::vector<VisitRecord>& visits) const;
    };

    static int patientCounter;

    Patient();
    Patient(std::string patientId, std::string patientName, int patientAge,
            int severity, int visits);
    Patient(const Patient& other);
    ~Patient() override;

    void update(const std::string& patientName, int patientAge);
    void update(int severity, int visits);
    void update(const std::string& patientName, int patientAge, int severity, int visits);

    void addCondition(const Condition& condition);
    void addVisit(const VisitRecord& visit);

    int getDiseaseSeverity() const;
    int getPreviousVisits() const;
    int getRiskScore() const;
    RiskCategory getRiskCategory() const;
    const std::vector<Condition>& getConditions() const;
    const std::vector<VisitRecord>& getHistory() const;

    void setRisk(int score, RiskCategory category);

    std::string generateReport() const override;
    void printSummary(std::ostream& out) const override;

    std::string serialize() const;
    static std::shared_ptr<Patient> deserialize(const std::string& line);

    friend std::ostream& operator<<(std::ostream& out, const Patient& patient);
    friend class RiskAnalyzer;
};

class PatientManager : public Reportable {
private:
    util::Repository<Patient> patients;

public:
    PatientManager();
    ~PatientManager() override;

    void addPatient(const std::shared_ptr<Patient>& patient);
    std::shared_ptr<Patient> createPatient(const std::string& id, const std::string& name,
                                           int age, int severity, int visits);
    bool updatePatient(const std::string& id, const std::string& name, int age,
                       int severity, int visits);
    bool deletePatient(const std::string& id);
    std::shared_ptr<Patient> searchPatient(const std::string& id) const;
    void analyzeAll(RiskAnalyzer& analyzer);

    const util::Repository<Patient>& getRepository() const;
    util::Repository<Patient>& getRepository();

    std::string generateReport() const override;
    std::string generateRiskAnalysisReport() const;
    void viewAll(std::ostream& out) const;
    void saveToFile(const std::string& filePath) const;
    void loadFromFile(const std::string& filePath);
};

} // namespace smart_hospital

#endif
