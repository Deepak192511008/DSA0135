#ifndef SMART_HOSPITAL_RISK_ANALYZER_H
#define SMART_HOSPITAL_RISK_ANALYZER_H

#include "patient.h"

#include <array>
#include <string>

namespace smart_hospital {

class RiskModel {
public:
    virtual ~RiskModel() = default;
    virtual int calculate(const Patient& patient) const = 0;
};

class RiskAnalyzer final : public RiskModel {
private:
    static int sumConditionImpactsRecursive(const std::vector<Condition>& conditions,
                                            std::size_t index);

public:
    RiskAnalyzer();
    ~RiskAnalyzer() override;

    int calculate(const Patient& patient) const override;
    void analyze(Patient& patient) const;

    static RiskCategory categoryFromScore(int score);
    static std::array<std::string, 4> categoryScale();
};

} // namespace smart_hospital

#endif
