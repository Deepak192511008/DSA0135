#pragma once

#include "scheduler.h"
#include "storage.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QStringList>
#include <QStackedWidget>
#include <QTableWidget>

class MainWindow : public QMainWindow {
    CsvRepository repository_;
    ReportManager reportManager_;
    AppData data_;
    Scheduler scheduler_;
    AnalyticsEngine analytics_;

    QWidget* central_ = nullptr;
    QStackedWidget* pages_ = nullptr;
    QLabel* utilizationLabel_ = nullptr;
    QLabel* workloadLabel_ = nullptr;
    QLabel* comfortLabel_ = nullptr;
    QLabel* clashLabel_ = nullptr;
    QTableWidget* facultyGraph_ = nullptr;
    QTableWidget* roomGraph_ = nullptr;

    QTableWidget* facultyTable_ = nullptr;
    QLineEdit* facultySearch_ = nullptr;
    QTableWidget* subjectTable_ = nullptr;
    QTableWidget* roomTable_ = nullptr;
    QTableWidget* batchTable_ = nullptr;
    QComboBox* timetableBatchCombo_ = nullptr;
    QTableWidget* timetableTable_ = nullptr;
    QTableWidget* clashTable_ = nullptr;

    void buildUi();
    QWidget* buildNavigation();
    QWidget* buildDashboardPage();
    QWidget* buildFacultyPage();
    QWidget* buildSubjectPage();
    QWidget* buildRoomPage();
    QWidget* buildBatchPage();
    QWidget* buildTimetablePage();
    QWidget* buildReportsPage();

    void refreshAll();
    void refreshDashboard();
    void refreshFacultyTable();
    void refreshSubjectTable();
    void refreshRoomTable();
    void refreshBatchTable();
    void refreshTimetable();
    void refreshClashes();
    void saveData();

    void addFaculty();
    void editFaculty();
    void deleteFaculty();
    void addSubject();
    void editSubject();
    void deleteSubject();
    void addRoom();
    void editRoom();
    void deleteRoom();
    void addBatch();
    void editBatch();
    void deleteBatch();
    void generateTimetable();
    void exportReports();
    void changePassword();
    void backupData();
    void restoreData();
    void applyTheme(bool dark);

public:
    explicit MainWindow(QWidget* parent = nullptr);
};
