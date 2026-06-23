# Project Report

## Project Name

AI Enhanced Smart Hospital Management System

## Team Size

2 members

## Module 1: Smart Patient Management System

The patient module supports adding, updating, deleting, searching, viewing, reporting, risk score analysis, and patient history tracking. The AI-inspired health risk prediction engine calculates a dynamic score from age, disease severity, previous visits, and existing conditions. Risk categories are Low, Medium, High, and Critical.

## Module 2: Smart Emergency and Resource Management

The emergency module uses a priority queue for severity ranking, smart waiting time prediction, emergency load analytics, and emergency statistics. The resource module manages ICU and general bed allocation with persistent bed occupancy tracking.

## C++17 Concepts Demonstrated

Classes and objects, default constructors, parameterized constructors, copy constructors, destructors, encapsulation, abstraction, abstract classes, pure virtual functions, single inheritance, multilevel inheritance, hierarchical inheritance, function overloading, function overriding, runtime polymorphism, compile-time polymorphism, friend function, friend class, static variables, static functions, private members, protected members, public members, dynamic memory allocation with new and delete, pointers, references, arrays, structures, enumerations, function templates, class templates, exception handling, file handling with ifstream, ofstream, and fstream, inline functions, namespaces, recursion, const functions, this pointer, type casting, nested classes, virtual functions, virtual destructor, aggregation, composition, lambda functions, unique_ptr, shared_ptr, vector, map, set, queue, priority_queue, sort, find_if, count_if, binary_search, auto, and range-based loops.

## Data Storage

`patients.txt` stores patient ID, name, age, risk score, risk category, disease severity, previous visits, existing conditions, and visit history.

`emergency.txt` stores emergency ID, severity, emergency type, waiting time, patient name, age, and risk snapshot.

`resources.txt` stores bed ID, bed type, occupancy status, and assigned patient ID.

## Build Command

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o SmartHospitalApp
```

## Run Command

```bash
./SmartHospitalApp
```

Windows PowerShell:

```powershell
.\SmartHospitalApp.exe
```

## ZIP-Ready Project Structure

```text
SmartHospital/
  include/
    hospital_base.h
    patient.h
    risk_analyzer.h
    emergency.h
    resource_manager.h
    utility.h
  src/
    hospital_base.cpp
    patient.cpp
    risk_analyzer.cpp
    emergency.cpp
    resource_manager.cpp
    utility.cpp
    main.cpp
  data/
    patients.txt
    emergency.txt
    resources.txt
  docs/
    README.md
    Project_Report.md
```
