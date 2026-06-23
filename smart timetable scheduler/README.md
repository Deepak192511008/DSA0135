# Smart Classroom & Timetable Scheduler

A Qt Widgets desktop application in C++ for higher education timetable generation, classroom utilization analytics, faculty workload tracking, clash detection, and student wellness optimization.

## Features

- Admin login with SHA-256 password validation and password change.
- Faculty, subject, classroom, and student batch management.
- Greedy constraint-based timetable generation.
- Clash prevention for faculty, room, and batch slots.
- Room type and capacity matching for theory/lab sessions.
- Faculty workload limits.
- Mandatory lunch break.
- Student wellness scoring from 0 to 100.
- Avoids excessive continuous theory classes, edge-slot overload, unnecessary gaps, and single-class days where possible.
- Timetable viewer with color coding for theory, lab, break, and fixed slots.
- Analytics dashboard with classroom utilization, workload, comfort score, clash statistics, faculty workload graph, and room utilization graph.
- CSV/TXT exports for timetable, faculty workload, classroom utilization, and student comfort reports.
- Dark mode, search filter for faculty, auto-save, backup, and restore.

## OOP And C++ Concepts Used

- `Person` base class and `Faculty` derived class.
- Encapsulation through private fields and public methods.
- Polymorphism through virtual `role()` and virtual destructors.
- STL containers: `vector`, `map`, `set`.
- Templates: generic `findById` helper with specializations.
- File handling with CSV/TXT persistence.
- Exception handling around save/export/backup workflows.
- Constructors and destructors across model classes.

## Build Requirements

- Qt 5 or Qt 6 with Widgets module.
- CMake 3.16 or newer.
- A C++17 capable compiler configured for your Qt installation.

## Build

```powershell
cmake -S . -B build -DCMAKE_PREFIX_PATH="C:\Qt\6.7.0\mingw_64"
cmake --build build
.\build\SmartClassroomScheduler.exe
```

Adjust `CMAKE_PREFIX_PATH` to the Qt installation on your computer. In Qt Creator, open `CMakeLists.txt`, configure the kit, then run.

## Login

- Default admin password: `admin123`
- Use `Security > Change Password` after first login.

## Data Files

The app reads and writes these files in `data/`:

- `admin.txt`
- `faculty.csv`
- `subjects.csv`
- `rooms.csv`
- `batches.csv`
- `timetable.csv`

If the data files are missing, the application recreates sample data automatically.

## Reports

Use the Reports page to generate files in `reports/`:

- `timetable_export.csv`
- `timetable_report.txt`
- `faculty_workload_report.txt`
- `classroom_utilization_report.txt`
- `student_comfort_report.txt`

