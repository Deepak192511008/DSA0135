#include "resource_manager.h"
#include "utility.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace smart_hospital {

Bed::Bed() : bedId("BED-UNKNOWN"), type(BedType::General), occupied(false), assignedPatientId("") {}

Bed::Bed(std::string id, BedType bedType, bool isOccupied, std::string patientId)
    : bedId(std::move(id)), type(bedType), occupied(isOccupied), assignedPatientId(std::move(patientId)) {}

Bed::Bed(const Bed& other)
    : bedId(other.bedId), type(other.type), occupied(other.occupied),
      assignedPatientId(other.assignedPatientId) {}

Bed::~Bed() = default;

const std::string& Bed::getBedId() const {
    return bedId;
}

BedType Bed::getType() const {
    return type;
}

bool Bed::isOccupied() const {
    return occupied;
}

const std::string& Bed::getAssignedPatientId() const {
    return assignedPatientId;
}

void Bed::occupy(const std::string& patientId) {
    if (occupied) {
        throw std::runtime_error("Bed is already occupied.");
    }
    occupied = true;
    assignedPatientId = patientId;
}

void Bed::release() {
    occupied = false;
    assignedPatientId.clear();
}

std::string Bed::generateReport() const {
    std::ostringstream out;
    out << bedId << " | " << toString(type) << " | "
        << (occupied ? "Occupied" : "Available") << " | "
        << (assignedPatientId.empty() ? "-" : assignedPatientId);
    return out.str();
}

std::string Bed::serialize() const {
    return util::join({
                          bedId,
                          toString(type),
                          occupied ? "1" : "0",
                          assignedPatientId,
                      },
                      '|');
}

std::unique_ptr<Bed> Bed::deserialize(const std::string& line) {
    const auto parts = util::split(line, '|');
    if (parts.size() < 3) {
        throw std::invalid_argument("Invalid bed record: " + line);
    }
    return std::make_unique<Bed>(parts[0],
                                 bedTypeFromString(parts[1]),
                                 util::toInt(parts[2], "Bed Occupancy") != 0,
                                 parts.size() > 3 ? parts[3] : "");
}

ResourceManager::ResourceManager() = default;

ResourceManager::~ResourceManager() = default;

void ResourceManager::addBed(std::unique_ptr<Bed> bed) {
    if (!bed) {
        throw std::invalid_argument("Cannot add an empty bed.");
    }
    capacityByType[bed->getType()]++;
    beds.push_back(std::move(bed));
}

Bed* ResourceManager::allocateBed(const std::string& patientId, BedType preferredType) {
    auto found = std::find_if(beds.begin(), beds.end(), [&](const std::unique_ptr<Bed>& bed) {
        return bed && bed->type == preferredType && !bed->occupied;
    });

    if (found == beds.end() && preferredType == BedType::ICU) {
        found = std::find_if(beds.begin(), beds.end(), [](const std::unique_ptr<Bed>& bed) {
            return bed && bed->type == BedType::General && !bed->occupied;
        });
    }

    if (found == beds.end()) {
        return nullptr;
    }

    (*found)->occupy(patientId);
    return found->get();
}

bool ResourceManager::releaseBed(const std::string& bedId) {
    auto found = std::find_if(beds.begin(), beds.end(), [&](const std::unique_ptr<Bed>& bed) {
        return bed && bed->bedId == bedId;
    });
    if (found == beds.end()) {
        return false;
    }
    (*found)->release();
    return true;
}

int ResourceManager::availableBeds(BedType type) const {
    return static_cast<int>(std::count_if(beds.begin(), beds.end(), [&](const std::unique_ptr<Bed>& bed) {
        return bed && bed->type == type && !bed->occupied;
    }));
}

int ResourceManager::occupiedBeds(BedType type) const {
    return static_cast<int>(std::count_if(beds.begin(), beds.end(), [&](const std::unique_ptr<Bed>& bed) {
        return bed && bed->type == type && bed->occupied;
    }));
}

const std::vector<std::unique_ptr<Bed>>& ResourceManager::getBeds() const {
    return beds;
}

std::string ResourceManager::generateReport() const {
    std::ostringstream out;
    out << "Resource Dashboard\n"
        << "==================\n"
        << "General Beds Available: " << availableBeds(BedType::General) << '\n'
        << "General Beds Occupied: " << occupiedBeds(BedType::General) << '\n'
        << "ICU Beds Available: " << availableBeds(BedType::ICU) << '\n'
        << "ICU Beds Occupied: " << occupiedBeds(BedType::ICU) << "\n\n"
        << bedAllocationReport();
    return out.str();
}

std::string ResourceManager::bedAllocationReport() const {
    std::ostringstream out;
    out << "Bed Allocation Report\n"
        << "=====================\n";
    for (const auto& bed : beds) {
        if (bed) {
            out << bed->generateReport() << '\n';
        }
    }
    return out.str();
}

void ResourceManager::seedDefaultBeds() {
    if (!beds.empty()) {
        return;
    }
    addBed(std::make_unique<Bed>("G-101", BedType::General));
    addBed(std::make_unique<Bed>("G-102", BedType::General));
    addBed(std::make_unique<Bed>("G-103", BedType::General));
    addBed(std::make_unique<Bed>("ICU-201", BedType::ICU));
    addBed(std::make_unique<Bed>("ICU-202", BedType::ICU));
}

void ResourceManager::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open resources file for writing: " + filePath);
    }
    for (const auto& bed : beds) {
        if (bed) {
            file << bed->serialize() << '\n';
        }
    }
}

void ResourceManager::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::runtime_error("Unable to open resources file for reading: " + filePath);
    }

    beds.clear();
    capacityByType.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!util::trim(line).empty()) {
            addBed(Bed::deserialize(line));
        }
    }
}

} // namespace smart_hospital
