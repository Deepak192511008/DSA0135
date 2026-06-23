#ifndef SMART_HOSPITAL_RESOURCE_MANAGER_H
#define SMART_HOSPITAL_RESOURCE_MANAGER_H

#include "hospital_base.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace smart_hospital {

class Bed : public Reportable {
private:
    std::string bedId;
    BedType type;
    bool occupied;
    std::string assignedPatientId;

public:
    Bed();
    Bed(std::string id, BedType bedType, bool isOccupied = false,
        std::string patientId = "");
    Bed(const Bed& other);
    ~Bed() override;

    const std::string& getBedId() const;
    BedType getType() const;
    bool isOccupied() const;
    const std::string& getAssignedPatientId() const;

    void occupy(const std::string& patientId);
    void release();

    std::string generateReport() const override;
    std::string serialize() const;
    static std::unique_ptr<Bed> deserialize(const std::string& line);

    friend class ResourceManager;
};

class ResourceManager : public Reportable {
private:
    std::vector<std::unique_ptr<Bed>> beds;
    std::map<BedType, int> capacityByType;

public:
    ResourceManager();
    ~ResourceManager() override;

    void addBed(std::unique_ptr<Bed> bed);
    Bed* allocateBed(const std::string& patientId, BedType preferredType);
    bool releaseBed(const std::string& bedId);
    int availableBeds(BedType type) const;
    int occupiedBeds(BedType type) const;
    const std::vector<std::unique_ptr<Bed>>& getBeds() const;

    std::string generateReport() const override;
    std::string bedAllocationReport() const;
    void seedDefaultBeds();
    void saveToFile(const std::string& filePath) const;
    void loadFromFile(const std::string& filePath);
};

} // namespace smart_hospital

#endif
