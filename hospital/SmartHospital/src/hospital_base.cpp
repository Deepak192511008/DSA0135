#include "hospital_base.h"
#include "utility.h"

#include <ostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace smart_hospital {

int HospitalEntity::totalEntities = 0;

Reportable::Reportable() = default;

Reportable::~Reportable() = default;

HospitalEntity::HospitalEntity() : id("UNASSIGNED") {
    ++totalEntities;
}

HospitalEntity::HospitalEntity(std::string entityId) : id(std::move(entityId)) {
    ++totalEntities;
}

HospitalEntity::HospitalEntity(const HospitalEntity& other) : id(other.id) {
    ++totalEntities;
}

HospitalEntity::~HospitalEntity() {
    --totalEntities;
}

Person::Person() : HospitalEntity(), name("Unknown"), age(0), address{} {}

Person::Person(std::string personId, std::string personName, int personAge)
    : HospitalEntity(std::move(personId)), name(std::move(personName)), age(personAge), address{} {}

Person::Person(const Person& other)
    : HospitalEntity(other), name(other.name), age(other.age), address(other.address) {}

Person::~Person() = default;

const std::string& Person::getName() const {
    return name;
}

int Person::getAge() const {
    return age;
}

const Address& Person::getAddress() const {
    return address;
}

void Person::setName(const std::string& personName) {
    this->name = personName;
}

void Person::setAge(int personAge) {
    if (personAge < 0 || personAge > 125) {
        throw std::out_of_range("Age must be between 0 and 125.");
    }
    this->age = personAge;
}

void Person::setAddress(const Address& personAddress) {
    this->address = personAddress;
}

std::string Person::generateReport() const {
    std::ostringstream out;
    out << "ID: " << id << '\n'
        << "Name: " << name << '\n'
        << "Age: " << age << '\n'
        << "City: " << address.city << '\n'
        << "State: " << address.state << '\n'
        << "Phone: " << address.phone << '\n';
    return out.str();
}

void Person::printSummary(std::ostream& out) const {
    out << id << " | " << name << " | Age " << age;
}

std::string toString(RiskCategory category) {
    switch (category) {
    case RiskCategory::Low:
        return "Low";
    case RiskCategory::Medium:
        return "Medium";
    case RiskCategory::High:
        return "High";
    case RiskCategory::Critical:
        return "Critical";
    }
    return "Unknown";
}

std::string toString(SeverityLevel severity) {
    switch (severity) {
    case SeverityLevel::Minor:
        return "Minor";
    case SeverityLevel::Moderate:
        return "Moderate";
    case SeverityLevel::Serious:
        return "Serious";
    case SeverityLevel::Severe:
        return "Severe";
    case SeverityLevel::Critical:
        return "Critical";
    }
    return "Unknown";
}

std::string toString(BedType type) {
    switch (type) {
    case BedType::General:
        return "General";
    case BedType::ICU:
        return "ICU";
    }
    return "Unknown";
}

RiskCategory riskCategoryFromString(const std::string& value) {
    const auto normalized = util::trim(value);
    if (normalized == "Low") {
        return RiskCategory::Low;
    }
    if (normalized == "Medium") {
        return RiskCategory::Medium;
    }
    if (normalized == "High") {
        return RiskCategory::High;
    }
    if (normalized == "Critical") {
        return RiskCategory::Critical;
    }
    throw std::invalid_argument("Invalid risk category: " + value);
}

SeverityLevel severityFromInt(int value) {
    if (value < 1 || value > 5) {
        throw std::out_of_range("Emergency severity must be from 1 to 5.");
    }
    return static_cast<SeverityLevel>(value);
}

BedType bedTypeFromString(const std::string& value) {
    const auto normalized = util::trim(value);
    if (normalized == "General" || normalized == "general") {
        return BedType::General;
    }
    if (normalized == "ICU" || normalized == "icu") {
        return BedType::ICU;
    }
    throw std::invalid_argument("Invalid bed type: " + value);
}

} // namespace smart_hospital
