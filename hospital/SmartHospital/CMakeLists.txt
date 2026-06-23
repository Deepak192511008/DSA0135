cmake_minimum_required(VERSION 3.15)

project(SmartHospitalApp)

include_directories(include)

add_executable(SmartHospitalApp
    src/main.cpp
    src/emergency.cpp
    src/hospital_base.cpp
    src/patient.cpp
    src/resource_manager.cpp
    src/risk_analyzer.cpp
    src/utility.cpp
)