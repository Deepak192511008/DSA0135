#include <iostream> 
#include <vector> 
using namespace std; 
 
// Member Class (Composition) 
class Doctor 
{ 
private: 
    string doctorName; 
 
public: 
    Doctor(string name = "Not Assigned") 
    { 
        doctorName = name; 
    } 
 
    void displayDoctor() 
    { 
        cout << "Doctor Assigned: " << doctorName << endl; 
    } 
}; 
 
// Abstract Base Class 
class Patient 
{ 
protected: 
    int patientID; 
    string patientName; 
    Doctor doctor; // Composition 
 
public: 
    Patient(int id, string name, string doc) 
        : patientID(id), patientName(name), doctor(doc) 
    { 
    } 
 
    virtual double calculateBill() = 0; // Pure Virtual Function 
 
    virtual void display() 
    { 
        cout << "\nPatient ID: " << patientID << endl; 
        cout << "Patient Name: " << patientName << endl; 
        doctor.displayDoctor(); 
    } 
 
    virtual ~Patient() {} 
}; 
 
// Virtual Base Class 
class InPatient : virtual public Patient 
{ 
protected: 
    double roomCharge; 
    double treatmentCost; 
 
public: 
    InPatient(int id, string name, string doc, 
              double room, double treatment) 
        : Patient(id, name, doc) 
    { 
        roomCharge = room; 
        treatmentCost = treatment; 
    } 
 
    double calculateBill() override 
    { 
        return roomCharge + treatmentCost; 
    } 
 
    void display() override 
    { 
        Patient::display(); 
        cout << "Type: InPatient" << endl; 
        cout << "Room Charge: " << roomCharge << endl; 
        cout << "Treatment Cost: " << treatmentCost << endl; 
        cout << "Bill: Rs." << calculateBill() << endl; 
    } 
}; 
 
class OutPatient : public Patient 
{ 
protected: 
    double consultationFee; 
 
public: 
    OutPatient(int id, string name, string doc, 
               double fee) 
        : Patient(id, name, doc) 
    { 
        consultationFee = fee; 
    } 
 
    double calculateBill() override 
    { 
        return consultationFee; 
    } 
 
    void display() override 
    { 
        Patient::display(); 
        cout << "Type: OutPatient" << endl; 
        cout << "Consultation Fee: " << consultationFee << endl; 
        cout << "Bill: Rs." << calculateBill() << endl; 
    } 
}; 
 
class EmergencyPatient : virtual public Patient 
{ 
protected: 
    double emergencyCharge; 
 
public: 
    EmergencyPatient(int id, string name, string doc, 
                     double emergency) 
        : Patient(id, name, doc) 
    { 
        emergencyCharge = emergency; 
    } 
 
    double calculateBill() override 
    { 
        return emergencyCharge; 
    } 
 
    void display() override 
    { 
        Patient::display(); 
        cout << "Type: Emergency Patient" << endl; 
        cout << "Emergency Charge: " << emergencyCharge << endl; 
        cout << "Bill: Rs." << calculateBill() << endl; 
    } 
}; 
 
// Multiple Inheritance + Virtual Base Class 
class CriticalPatient : public InPatient, public EmergencyPatient 
{ 
public: 
    CriticalPatient(int id, string name, string doc, 
                    double room, double treatment, 
                    double emergency) 
        : Patient(id, name, doc), 
          InPatient(id, name, doc, room, treatment), 
          EmergencyPatient(id, name, doc, emergency) 
    { 
    } 
 
    double calculateBill() override 
    { 
        return roomCharge + treatmentCost + emergencyCharge; 
    } 
 
    void display() override 
    { 
        Patient::display(); 
 
        cout << "Type: Critical Patient" << endl; 
        cout << "Room Charge: " << roomCharge << endl; 
        cout << "Treatment Cost: " << treatmentCost << endl; 
        cout << "Emergency Charge: " << emergencyCharge << endl; 
 
        // Using this pointer 
        cout << "Total Bill = Rs." << this->calculateBill() << endl; 
    } 
}; 
 
int main() 
{ 
    int choice; 
 
    do 
    { 
        cout << "\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n"; 
        cout << "1. InPatient\n"; 
        cout << "2. OutPatient\n"; 
        cout << "3. Emergency Patient\n"; 
        cout << "4. Critical Patient\n"; 
        cout << "5. Exit\n"; 
        cout << "Enter Choice: "; 
        cin >> choice; 
 
        Patient *p = nullptr; // Pointer to Base Class 
 
        int id; 
        string name, doctor; 
 
        if (choice >= 1 && choice <= 4) 
        { 
            cout << "Enter Patient ID: "; 
            cin >> id; 
 
            cin.ignore(); 
 
            cout << "Enter Patient Name: "; 
            getline(cin, name); 
 
            cout << "Enter Doctor Name: "; 
            getline(cin, doctor); 
        } 
 
        switch (choice) 
        { 
        case 1: 
        { 
            double room, treatment; 
 
            cout << "Enter Room Charge: "; 
            cin >> room; 
 
            cout << "Enter Treatment Cost: "; 
            cin >> treatment; 
 
            p = new InPatient(id, name, doctor, room, treatment); 
            break; 
        } 
 
        case 2: 
        { 
            double fee; 
 
            cout << "Enter Consultation Fee: "; 
            cin >> fee; 
 
            p = new OutPatient(id, name, doctor, fee); 
            break; 
        } 
 
        case 3: 
        { 
            double emergency; 
 
            cout << "Enter Emergency Charge: "; 
            cin >> emergency; 
 
            p = new EmergencyPatient(id, name, doctor, emergency); 
            break; 
        } 
 
        case 4: 
        { 
            double room, treatment, emergency; 
 
            cout << "Enter Room Charge: "; 
            cin >> room; 
 
            cout << "Enter Treatment Cost: "; 
            cin >> treatment; 
 
            cout << "Enter Emergency Charge: "; 
            cin >> emergency; 
 
            p = new CriticalPatient(id, name, doctor, 
                                    room, treatment, emergency); 
            break; 
        } 
 
        case 5: 
            cout << "\nThank You!\n"; 
            return 0; 
 
        default: 
            cout << "\nInvalid Choice!\n"; 
        } 
 
        if (p != nullptr) 
        { 
            cout << "\n========== PATIENT DETAILS ==========\n"; 
            p->display(); // Runtime Polymorphism 
 
            delete p; // Dynamic Memory Deallocation 
        } 
 
    } while (choice != 5); 
 
    return 0; 
} 
