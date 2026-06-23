#ifndef SMART_HOSPITAL_HOSPITAL_BASE_H
#define SMART_HOSPITAL_HOSPITAL_BASE_H

#include <iosfwd>
#include <string>

namespace smart_hospital {

enum class RiskCategory {
    Low,
    Medium,
    High,
    Critical
};

enum class SeverityLevel {
    Minor = 1,
    Moderate = 2,
    Serious = 3,
    Severe = 4,
    Critical = 5
};

enum class BedType {
    General,
    ICU
};

struct Address {
    std::string city;
    std::string state;
    std::string phone;
};

class Reportable {
public:
    Reportable();
    virtual ~Reportable();
    virtual std::string generateReport() const = 0;
};

class HospitalEntity : public Reportable {
protected:
    std::string id;

public:
    static int totalEntities;

    HospitalEntity();
    explicit HospitalEntity(std::string entityId);
    HospitalEntity(const HospitalEntity& other);
    ~HospitalEntity() override;

    inline const std::string& getId() const {
        return id;
    }

    inline void setId(const std::string& entityId) {
        this->id = entityId;
    }

    virtual void printSummary(std::ostream& out) const = 0;
};

class Person : public HospitalEntity {
protected:
    std::string name;
    int age;
    Address address;

public:
    Person();
    Person(std::string personId, std::string personName, int personAge);
    Person(const Person& other);
    ~Person() override;

    const std::string& getName() const;
    int getAge() const;
    const Address& getAddress() const;

    void setName(const std::string& personName);
    void setAge(int personAge);
    void setAddress(const Address& personAddress);

    std::string generateReport() const override;
    void printSummary(std::ostream& out) const override;
};

std::string toString(RiskCategory category);
std::string toString(SeverityLevel severity);
std::string toString(BedType type);

RiskCategory riskCategoryFromString(const std::string& value);
SeverityLevel severityFromInt(int value);
BedType bedTypeFromString(const std::string& value);

} // namespace smart_hospital

#endif
