#include "emergency.h"
#include "patient.h"
#include "resource_manager.h"
#include "risk_analyzer.h"
#include "utility.h"

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


using namespace smart_hospital;

namespace {

const std::string patientFile = "data/patients.txt";
const std::string emergencyFile = "data/emergency.txt";
const std::string resourcesFile = "data/resources.txt";

int readInt(const std::string& prompt, int low, int high) {
    while (true) {
        std::cout << prompt;
        std::string text;
        std::getline(std::cin, text);
        try {
            const int value = util::toInt(text, prompt);
            if (value < low || value > high) {
                throw std::out_of_range("Value outside allowed range.");
            }
            return value;
        } catch (const std::exception& error) {
            std::cout << "Invalid input: " << error.what() << '\n';
        }
    }
}

std::string readText(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        value = util::trim(value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Value cannot be empty.\n";
    }
}

void pause() {
    std::cout << "\nPress Enter to continue...";
    std::string ignored;
    std::getline(std::cin, ignored);
}

void saveAll(const PatientManager& patients, const EmergencyManager& emergencies,
             const ResourceManager& resources) {
    patients.saveToFile(patientFile);
    emergencies.saveToFile(emergencyFile);
    resources.saveToFile(resourcesFile);
    std::cout << "All data saved.\n";
}

void loadAll(PatientManager& patients, EmergencyManager& emergencies,
             ResourceManager& resources, RiskAnalyzer& analyzer) {
    util::ensureDataFile(patientFile);
    util::ensureDataFile(emergencyFile);
    util::ensureDataFile(resourcesFile);

    patients.loadFromFile(patientFile);
    emergencies.loadFromFile(emergencyFile);
    resources.loadFromFile(resourcesFile);
    if (resources.getBeds().empty()) {
        resources.seedDefaultBeds();
    }
    patients.analyzeAll(analyzer);
    std::cout << "All data loaded.\n";
}

void addPatient(PatientManager& manager, RiskAnalyzer& analyzer) {
    const std::string id = readText("Patient ID: ");
    const std::string name = readText("Name: ");
    const int age = readInt("Age: ", 0, 125);
    const int severity = readInt("Disease severity (0-10): ", 0, 10);
    const int visits = readInt("Previous visits: ", 0, 1000);

    auto patient = manager.createPatient(id, name, age, severity, visits);

    const int conditionCount = readInt("Existing condition count: ", 0, 20);
    for (int index = 0; index < conditionCount; ++index) {
        const std::string conditionName = readText("Condition name: ");
        const int impact = readInt("Condition impact (0-25): ", 0, 25);
        patient->addCondition({conditionName, impact});
    }
    patient->addVisit({util::currentDateTime(), "Patient registered"});
    analyzer.analyze(*patient);
    std::cout << "Patient added with risk score " << patient->getRiskScore()
              << " (" << toString(patient->getRiskCategory()) << ").\n";
}

void patientMenu(PatientManager& manager, RiskAnalyzer& analyzer) {
    while (true) {
        std::cout << "\nPatient Management\n"
                  << "1. Add Patient\n"
                  << "2. Update Patient\n"
                  << "3. Delete Patient\n"
                  << "4. Search Patient\n"
                  << "5. View All Patients\n"
                  << "6. Generate Patient Report\n"
                  << "7. Risk Score Analysis\n"
                  << "8. Back\n";
        const int choice = readInt("Choice: ", 1, 8);

        if (choice == 1) {
            addPatient(manager, analyzer);
        } else if (choice == 2) {
            const std::string id = readText("Patient ID: ");
            const std::string name = readText("Updated name: ");
            const int age = readInt("Updated age: ", 0, 125);
            const int severity = readInt("Updated disease severity (0-10): ", 0, 10);
            const int visits = readInt("Updated previous visits: ", 0, 1000);
            if (manager.updatePatient(id, name, age, severity, visits)) {
                auto patient = manager.searchPatient(id);
                if (patient) {
                    analyzer.analyze(*patient);
                }
                std::cout << "Patient updated.\n";
            } else {
                std::cout << "Patient not found.\n";
            }
        } else if (choice == 3) {
            std::cout << (manager.deletePatient(readText("Patient ID: ")) ? "Patient deleted.\n"
                                                                          : "Patient not found.\n");
        } else if (choice == 4) {
            auto patient = manager.searchPatient(readText("Patient ID: "));
            std::cout << (patient ? patient->generateReport() : "Patient not found.\n");
        } else if (choice == 5) {
            manager.viewAll(std::cout);
        } else if (choice == 6) {
            const std::string id = readText("Patient ID: ");
            auto patient = manager.searchPatient(id);
            std::cout << (patient ? patient->generateReport() : "Patient not found.\n");
        } else if (choice == 7) {
            manager.analyzeAll(analyzer);
            std::cout << manager.generateRiskAnalysisReport();
        } else {
            return;
        }
        pause();
    }
}

void emergencyMenu(EmergencyManager& manager, ResourceManager& resources) {
    while (true) {
        std::cout << "\nEmergency Management\n"
                  << "1. Register Emergency Patient\n"
                  << "2. Emergency Severity Ranking\n"
                  << "3. Process Priority Queue\n"
                  << "4. ICU Bed Allocation\n"
                  << "5. General Bed Allocation\n"
                  << "6. Waiting Time Prediction\n"
                  << "7. Resource Dashboard\n"
                  << "8. Emergency Statistics\n"
                  << "9. Back\n";
        const int choice = readInt("Choice: ", 1, 9);

        if (choice == 1) {
            const std::string id = readText("Emergency ID: ");
            const std::string name = readText("Patient name: ");
            const int age = readInt("Patient age: ", 0, 125);
            const int severity = readInt("Severity (1 Minor - 5 Critical): ", 1, 5);
            const std::string type = readText("Emergency type: ");
            const int wait = manager.predictWaitingTime(severityFromInt(severity));
            EmergencyCase emergency(id, name, age, severityFromInt(severity), type, wait);
            manager.registerEmergency(emergency);
            const BedType bedType = severity >= 4 ? BedType::ICU : BedType::General;
            Bed* bed = resources.allocateBed(id, bedType);
            std::cout << "Emergency registered. Predicted waiting time: " << wait << " minutes.\n";
            std::cout << (bed ? "Allocated bed: " + bed->getBedId() + "\n" : "No bed available.\n");
        } else if (choice == 2) {
            std::cout << manager.generateReport();
        } else if (choice == 3) {
            try {
                EmergencyCase next = manager.processNext();
                std::cout << "Next priority case:\n" << next.generateReport();
            } catch (const std::exception& error) {
                std::cout << error.what() << '\n';
            }
        } else if (choice == 4 || choice == 5) {
            const std::string patientId = readText("Patient/Emergency ID: ");
            const BedType type = choice == 4 ? BedType::ICU : BedType::General;
            Bed* bed = resources.allocateBed(patientId, type);
            std::cout << (bed ? "Allocated bed: " + bed->getBedId() + "\n" : "No matching bed available.\n");
        } else if (choice == 6) {
            const int severity = readInt("Severity (1 Minor - 5 Critical): ", 1, 5);
            std::cout << "Predicted waiting time: "
                      << manager.predictWaitingTime(severityFromInt(severity)) << " minutes\n";
        } else if (choice == 7) {
            std::cout << resources.generateReport();
        } else if (choice == 8) {
            std::cout << manager.generateStatistics();
        } else {
            return;
        }
        pause();
    }
}

void resourceMenu(ResourceManager& resources) {
    while (true) {
        std::cout << "\nResource Management\n"
                  << "1. View Resource Dashboard\n"
                  << "2. Allocate Bed\n"
                  << "3. Release Bed\n"
                  << "4. Add Bed\n"
                  << "5. Back\n";
        const int choice = readInt("Choice: ", 1, 5);

        if (choice == 1) {
            std::cout << resources.generateReport();
        } else if (choice == 2) {
            const std::string patientId = readText("Patient ID: ");
            const int type = readInt("Bed type (1 General, 2 ICU): ", 1, 2);
            Bed* bed = resources.allocateBed(patientId, type == 1 ? BedType::General : BedType::ICU);
            std::cout << (bed ? "Allocated bed: " + bed->getBedId() + "\n" : "No bed available.\n");
        } else if (choice == 3) {
            std::cout << (resources.releaseBed(readText("Bed ID: ")) ? "Bed released.\n"
                                                                      : "Bed not found.\n");
        } else if (choice == 4) {
            const std::string bedId = readText("Bed ID: ");
            const int type = readInt("Bed type (1 General, 2 ICU): ", 1, 2);
            resources.addBed(std::make_unique<Bed>(bedId, type == 1 ? BedType::General : BedType::ICU));
            std::cout << "Bed added.\n";
        } else {
            return;
        }
        pause();
    }
}

void reportsMenu(PatientManager& patients, EmergencyManager& emergencies, ResourceManager& resources) {
    while (true) {
        std::cout << "\nReports\n"
                  << "1. Patient Report\n"
                  << "2. Risk Analysis Report\n"
                  << "3. Emergency Report\n"
                  << "4. Bed Allocation Report\n"
                  << "5. System Statistics\n"
                  << "6. Back\n";
        const int choice = readInt("Choice: ", 1, 6);

        if (choice == 1) {
            std::cout << patients.generateReport();
        } else if (choice == 2) {
            std::cout << patients.generateRiskAnalysisReport();
        } else if (choice == 3) {
            std::cout << emergencies.generateReport();
        } else if (choice == 4) {
            std::cout << resources.bedAllocationReport();
        } else if (choice == 5) {
            std::vector<Reportable*> modules = {&patients, &emergencies, &resources};
            for (const auto* module : modules) {
                std::cout << module->generateReport() << '\n';
            }
            std::cout << "Live Entity Counter: " << HospitalEntity::totalEntities << '\n'
                      << "Patient Counter: " << Patient::patientCounter << '\n'
                      << "Emergency Counter: " << EmergencyManager::totalEmergencies << '\n';
        } else {
            return;
        }
        pause();
    }
}

} // namespace

int main() {
    PatientManager patientManager;
    EmergencyManager emergencyManager;
    ResourceManager resourceManager;
    RiskAnalyzer riskAnalyzer;

    try {
        loadAll(patientManager, emergencyManager, resourceManager, riskAnalyzer);
    } catch (const std::exception& error) {
        std::cout << "Startup load warning: " << error.what() << '\n';
        resourceManager.seedDefaultBeds();
    }

    while (true) {
        try {
            std::cout << "\nSmart Hospital Management System\n"
                      << "1. Patient Management\n"
                      << "2. Emergency Management\n"
                      << "3. Resource Management\n"
                      << "4. Reports\n"
                      << "5. Save Data\n"
                      << "6. Load Data\n"
                      << "7. Exit\n";

            const int choice = readInt("Choice: ", 1, 7);
            if (choice == 1) {
                patientMenu(patientManager, riskAnalyzer);
            } else if (choice == 2) {
                emergencyMenu(emergencyManager, resourceManager);
            } else if (choice == 3) {
                resourceMenu(resourceManager);
            } else if (choice == 4) {
                reportsMenu(patientManager, emergencyManager, resourceManager);
            } else if (choice == 5) {
                saveAll(patientManager, emergencyManager, resourceManager);
                pause();
            } else if (choice == 6) {
                loadAll(patientManager, emergencyManager, resourceManager, riskAnalyzer);
                pause();
            } else {
                saveAll(patientManager, emergencyManager, resourceManager);
                std::cout << "Goodbye.\n";
                return 0;
            }
        } catch (const std::exception& error) {
            std::cout << "Operation failed: " << error.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
