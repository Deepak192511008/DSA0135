#include "risk_analyzer.h"
#include "utility.h"

#include <algorithm>

namespace smart_hospital {

RiskAnalyzer::RiskAnalyzer() = default;

RiskAnalyzer::~RiskAnalyzer() = default;

int RiskAnalyzer::sumConditionImpactsRecursive(const std::vector<Condition>& conditions,
                                               std::size_t index) {
    if (index >= conditions.size()) {
        return 0;
    }
    return conditions[index].severityImpact + sumConditionImpactsRecursive(conditions, index + 1);
}

int RiskAnalyzer::calculate(const Patient& patient) const {
    const int ageFactor = patient.age >= 70 ? 30 : patient.age >= 50 ? 20 : patient.age >= 30 ? 10 : 5;
    const int severityFactor = util::clampValue(patient.diseaseSeverity, 0, 10) * 5;
    const int visitsFactor = std::min(patient.previousVisits * 3, 25);
    const int conditionFactor = sumConditionImpactsRecursive(patient.existingConditions, 0);
    const int rawScore = ageFactor + severityFactor + visitsFactor + conditionFactor;
    return util::clampValue(rawScore, 0, 100);
}

void RiskAnalyzer::analyze(Patient& patient) const {
    const int score = calculate(patient);
    patient.setRisk(score, categoryFromScore(score));
}

RiskCategory RiskAnalyzer::categoryFromScore(int score) {
    if (score < 30) {
        return RiskCategory::Low;
    }
    if (score < 55) {
        return RiskCategory::Medium;
    }
    if (score < 80) {
        return RiskCategory::High;
    }
    return RiskCategory::Critical;
}

std::array<std::string, 4> RiskAnalyzer::categoryScale() {
    return {"Low Risk", "Medium Risk", "High Risk", "Critical Risk"};
}

} // namespace smart_hospital
