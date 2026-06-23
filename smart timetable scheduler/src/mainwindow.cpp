#include "mainwindow.h"

#include <QAbstractItemView>
#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include <algorithm>
#include <exception>
#include <initializer_list>

namespace {
QString qs(const std::string& value) { return QString::fromStdString(value); }
std::string ss(const QString& value) { return value.trimmed().toStdString(); }

QStringList makeStringList(std::initializer_list<const char*> values)
{
    QStringList list;
    for (const char* value : values) {
        list.append(QString::fromUtf8(value));
    }
    return list;
}

QTableWidgetItem* item(const QString& value)
{
    auto* tableItem = new QTableWidgetItem(value);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    return tableItem;
}

QPushButton* navButton(const QString& text)
{
    auto* button = new QPushButton(text);
    button->setMinimumHeight(42);
    button->setCursor(Qt::PointingHandCursor);
    return button;
}

void prepareTable(QTableWidget* table)
{
    table->setAlternatingRowColors(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setStretchLastSection(true);
    table->verticalHeader()->setVisible(false);
}

int selectedRow(QTableWidget* table)
{
    const auto rows = table->selectionModel()->selectedRows();
    return rows.isEmpty() ? -1 : rows.first().row();
}

class FacultyDialog : public QDialog {
public:
    QLineEdit* id = new QLineEdit;
    QLineEdit* name = new QLineEdit;
    QLineEdit* dept = new QLineEdit;
    QLineEdit* subjects = new QLineEdit;
    QSpinBox* maxHours = new QSpinBox;
    QSpinBox* leaves = new QSpinBox;

    FacultyDialog(QWidget* parent, const Faculty* faculty = nullptr) : QDialog(parent)
    {
        setWindowTitle(faculty ? "Edit Faculty" : "Add Faculty");
        maxHours->setRange(1, 40);
        leaves->setRange(0, 60);
        auto* form = new QFormLayout(this);
        form->addRow("Faculty ID", id);
        form->addRow("Name", name);
        form->addRow("Department", dept);
        form->addRow("Subjects (use |)", subjects);
        form->addRow("Max hours/week", maxHours);
        form->addRow("Leave count", leaves);
        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
        if (faculty) {
            id->setText(qs(faculty->id()));
            id->setReadOnly(true);
            name->setText(qs(faculty->name()));
            dept->setText(qs(faculty->department()));
            subjects->setText(qs(joinList(faculty->subjects())));
            maxHours->setValue(faculty->maxHoursPerWeek());
            leaves->setValue(faculty->leaveCount());
        } else {
            maxHours->setValue(16);
        }
    }
};

class SubjectDialog : public QDialog {
public:
    QLineEdit* code = new QLineEdit;
    QLineEdit* name = new QLineEdit;
    QSpinBox* hours = new QSpinBox;
    QComboBox* type = new QComboBox;
    QComboBox* faculty = new QComboBox;
    QSpinBox* difficulty = new QSpinBox;

    SubjectDialog(QWidget* parent, const std::vector<Faculty>& facultyList, const Subject* subject = nullptr) : QDialog(parent)
    {
        setWindowTitle(subject ? "Edit Subject" : "Add Subject");
        hours->setRange(1, 10);
        difficulty->setRange(1, 5);
        type->addItems(makeStringList({"Theory", "Lab"}));
        for (const auto& f : facultyList) {
            faculty->addItem(qs(f.id() + " - " + f.name()), qs(f.id()));
        }
        auto* form = new QFormLayout(this);
        form->addRow("Subject code", code);
        form->addRow("Subject name", name);
        form->addRow("Weekly hours", hours);
        form->addRow("Subject type", type);
        form->addRow("Assigned faculty", faculty);
        form->addRow("Difficulty", difficulty);
        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
        if (subject) {
            code->setText(qs(subject->code()));
            code->setReadOnly(true);
            name->setText(qs(subject->name()));
            hours->setValue(subject->weeklyHours());
            type->setCurrentText(qs(toString(subject->type())));
            const int facultyIndex = faculty->findData(qs(subject->assignedFacultyId()));
            if (facultyIndex >= 0) {
                faculty->setCurrentIndex(facultyIndex);
            }
            difficulty->setValue(subject->difficulty());
        } else {
            hours->setValue(3);
            difficulty->setValue(3);
        }
    }
};

class RoomDialog : public QDialog {
public:
    QLineEdit* room = new QLineEdit;
    QSpinBox* capacity = new QSpinBox;
    QComboBox* type = new QComboBox;
    QCheckBox* available = new QCheckBox("Available");

    RoomDialog(QWidget* parent, const Classroom* classroom = nullptr) : QDialog(parent)
    {
        setWindowTitle(classroom ? "Edit Classroom" : "Add Classroom");
        capacity->setRange(1, 300);
        type->addItems(makeStringList({"Classroom", "Lab"}));
        auto* form = new QFormLayout(this);
        form->addRow("Room number", room);
        form->addRow("Capacity", capacity);
        form->addRow("Room type", type);
        form->addRow("", available);
        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
        if (classroom) {
            room->setText(qs(classroom->roomNumber()));
            room->setReadOnly(true);
            capacity->setValue(classroom->capacity());
            type->setCurrentText(qs(toString(classroom->type())));
            available->setChecked(classroom->available());
        } else {
            capacity->setValue(60);
            available->setChecked(true);
        }
    }
};

class BatchDialog : public QDialog {
public:
    QLineEdit* id = new QLineEdit;
    QSpinBox* semester = new QSpinBox;
    QLineEdit* section = new QLineEdit;
    QSpinBox* count = new QSpinBox;

    BatchDialog(QWidget* parent, const Batch* batch = nullptr) : QDialog(parent)
    {
        setWindowTitle(batch ? "Edit Batch" : "Add Batch");
        semester->setRange(1, 12);
        count->setRange(1, 300);
        auto* form = new QFormLayout(this);
        form->addRow("Batch ID", id);
        form->addRow("Semester", semester);
        form->addRow("Section", section);
        form->addRow("Student count", count);
        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        form->addRow(buttons);
        connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
        if (batch) {
            id->setText(qs(batch->id()));
            id->setReadOnly(true);
            semester->setValue(batch->semester());
            section->setText(qs(batch->section()));
            count->setValue(batch->studentCount());
        } else {
            semester->setValue(1);
            count->setValue(60);
        }
    }
};
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), repository_("data"), reportManager_("reports")
{
    setWindowTitle("Smart Classroom & Timetable Scheduler");
    resize(1280, 760);
    data_ = repository_.loadAll();
    buildUi();
    refreshAll();
}

void MainWindow::buildUi()
{
    auto* fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Auto Save", this, [this]() { saveData(); });
    fileMenu->addAction("Backup Data", this, [this]() { backupData(); });
    fileMenu->addAction("Restore Backup", this, [this]() { restoreData(); });
    auto* securityMenu = menuBar()->addMenu("Security");
    securityMenu->addAction("Change Password", this, [this]() { changePassword(); });
    auto* viewMenu = menuBar()->addMenu("View");
    auto* darkAction = viewMenu->addAction("Dark Mode");
    darkAction->setCheckable(true);
    connect(darkAction, &QAction::toggled, this, [this](bool on) { applyTheme(on); });

    central_ = new QWidget;
    auto* layout = new QHBoxLayout(central_);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    pages_ = new QStackedWidget;
    layout->addWidget(buildNavigation());
    layout->addWidget(pages_, 1);

    pages_->addWidget(buildDashboardPage());
    pages_->addWidget(buildFacultyPage());
    pages_->addWidget(buildSubjectPage());
    pages_->addWidget(buildRoomPage());
    pages_->addWidget(buildBatchPage());
    pages_->addWidget(buildTimetablePage());
    pages_->addWidget(buildReportsPage());

    setCentralWidget(central_);
    applyTheme(false);
}

QWidget* MainWindow::buildNavigation()
{
    auto* nav = new QWidget;
    nav->setObjectName("navigation");
    nav->setFixedWidth(220);
    auto* layout = new QVBoxLayout(nav);
    auto* title = new QLabel("College ERP\nScheduler");
    title->setObjectName("navTitle");
    layout->addWidget(title);
    const QStringList names = makeStringList({"Dashboard", "Faculty", "Subjects", "Rooms", "Batches", "Timetable", "Reports"});
    for (int i = 0; i < names.size(); ++i) {
        auto* button = navButton(names[i]);
        connect(button, &QPushButton::clicked, this, [this, i]() { pages_->setCurrentIndex(i); });
        layout->addWidget(button);
    }
    layout->addStretch();
    return nav;
}

QWidget* MainWindow::buildDashboardPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* title = new QLabel("Analytics Dashboard");
    title->setObjectName("pageTitle");
    auto* metrics = new QGridLayout;
    utilizationLabel_ = new QLabel;
    workloadLabel_ = new QLabel;
    comfortLabel_ = new QLabel;
    clashLabel_ = new QLabel;
    metrics->addWidget(utilizationLabel_, 0, 0);
    metrics->addWidget(workloadLabel_, 0, 1);
    metrics->addWidget(comfortLabel_, 1, 0);
    metrics->addWidget(clashLabel_, 1, 1);

    facultyGraph_ = new QTableWidget;
    roomGraph_ = new QTableWidget;
    prepareTable(facultyGraph_);
    prepareTable(roomGraph_);
    facultyGraph_->setColumnCount(3);
    facultyGraph_->setHorizontalHeaderLabels(makeStringList({"Faculty", "Hours", "Workload %"}));
    roomGraph_->setColumnCount(3);
    roomGraph_->setHorizontalHeaderLabels(makeStringList({"Room", "Hours", "Utilization %"}));

    layout->addWidget(title);
    layout->addLayout(metrics);
    layout->addWidget(new QLabel("Faculty workload graph"));
    layout->addWidget(facultyGraph_, 1);
    layout->addWidget(new QLabel("Room utilization graph"));
    layout->addWidget(roomGraph_, 1);
    return page;
}

QWidget* MainWindow::buildFacultyPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* top = new QHBoxLayout;
    facultySearch_ = new QLineEdit;
    facultySearch_->setPlaceholderText("Search faculty");
    auto* add = new QPushButton("Add");
    auto* edit = new QPushButton("Edit");
    auto* del = new QPushButton("Delete");
    top->addWidget(facultySearch_, 1);
    top->addWidget(add);
    top->addWidget(edit);
    top->addWidget(del);
    facultyTable_ = new QTableWidget;
    prepareTable(facultyTable_);
    facultyTable_->setColumnCount(6);
    facultyTable_->setHorizontalHeaderLabels(makeStringList({"ID", "Name", "Department", "Subjects", "Max Hours", "Leaves"}));
    layout->addLayout(top);
    layout->addWidget(facultyTable_);
    connect(add, &QPushButton::clicked, this, [this]() { addFaculty(); });
    connect(edit, &QPushButton::clicked, this, [this]() { editFaculty(); });
    connect(del, &QPushButton::clicked, this, [this]() { deleteFaculty(); });
    connect(facultySearch_, &QLineEdit::textChanged, this, [this]() { refreshFacultyTable(); });
    return page;
}

QWidget* MainWindow::buildSubjectPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* top = new QHBoxLayout;
    auto* add = new QPushButton("Add");
    auto* edit = new QPushButton("Edit");
    auto* del = new QPushButton("Delete");
    top->addStretch();
    top->addWidget(add);
    top->addWidget(edit);
    top->addWidget(del);
    subjectTable_ = new QTableWidget;
    prepareTable(subjectTable_);
    subjectTable_->setColumnCount(6);
    subjectTable_->setHorizontalHeaderLabels(makeStringList({"Code", "Name", "Weekly Hours", "Type", "Faculty", "Difficulty"}));
    layout->addLayout(top);
    layout->addWidget(subjectTable_);
    connect(add, &QPushButton::clicked, this, [this]() { addSubject(); });
    connect(edit, &QPushButton::clicked, this, [this]() { editSubject(); });
    connect(del, &QPushButton::clicked, this, [this]() { deleteSubject(); });
    return page;
}

QWidget* MainWindow::buildRoomPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* top = new QHBoxLayout;
    auto* add = new QPushButton("Add");
    auto* edit = new QPushButton("Edit");
    auto* del = new QPushButton("Delete");
    top->addStretch();
    top->addWidget(add);
    top->addWidget(edit);
    top->addWidget(del);
    roomTable_ = new QTableWidget;
    prepareTable(roomTable_);
    roomTable_->setColumnCount(4);
    roomTable_->setHorizontalHeaderLabels(makeStringList({"Room", "Capacity", "Type", "Availability"}));
    layout->addLayout(top);
    layout->addWidget(roomTable_);
    connect(add, &QPushButton::clicked, this, [this]() { addRoom(); });
    connect(edit, &QPushButton::clicked, this, [this]() { editRoom(); });
    connect(del, &QPushButton::clicked, this, [this]() { deleteRoom(); });
    return page;
}

QWidget* MainWindow::buildBatchPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* top = new QHBoxLayout;
    auto* add = new QPushButton("Add");
    auto* edit = new QPushButton("Edit");
    auto* del = new QPushButton("Delete");
    top->addStretch();
    top->addWidget(add);
    top->addWidget(edit);
    top->addWidget(del);
    batchTable_ = new QTableWidget;
    prepareTable(batchTable_);
    batchTable_->setColumnCount(4);
    batchTable_->setHorizontalHeaderLabels(makeStringList({"Batch", "Semester", "Section", "Students"}));
    layout->addLayout(top);
    layout->addWidget(batchTable_);
    connect(add, &QPushButton::clicked, this, [this]() { addBatch(); });
    connect(edit, &QPushButton::clicked, this, [this]() { editBatch(); });
    connect(del, &QPushButton::clicked, this, [this]() { deleteBatch(); });
    return page;
}

QWidget* MainWindow::buildTimetablePage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* top = new QHBoxLayout;
    timetableBatchCombo_ = new QComboBox;
    auto* generate = new QPushButton("Generate Optimized Timetable");
    top->addWidget(new QLabel("Batch"));
    top->addWidget(timetableBatchCombo_);
    top->addStretch();
    top->addWidget(generate);
    timetableTable_ = new QTableWidget(Timetable::Slots, Timetable::Days);
    prepareTable(timetableTable_);
    QStringList days;
    for (const auto& day : Timetable::dayNames()) {
        days.append(qs(day));
    }
    QStringList slotLabels;
    for (const auto& slot : Timetable::slotNames()) {
        slotLabels.append(qs(slot));
    }
    timetableTable_->setHorizontalHeaderLabels(days);
    timetableTable_->setVerticalHeaderLabels(slotLabels);
    timetableTable_->verticalHeader()->setVisible(true);
    timetableTable_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    timetableTable_->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    clashTable_ = new QTableWidget;
    prepareTable(clashTable_);
    clashTable_->setColumnCount(3);
    clashTable_->setHorizontalHeaderLabels(makeStringList({"Type", "Message", "Suggestion"}));
    layout->addLayout(top);
    layout->addWidget(timetableTable_, 3);
    layout->addWidget(new QLabel("Clash detection and automatic suggestions"));
    layout->addWidget(clashTable_, 1);
    connect(generate, &QPushButton::clicked, this, [this]() { generateTimetable(); });
    connect(timetableBatchCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { refreshTimetable(); });
    return page;
}

QWidget* MainWindow::buildReportsPage()
{
    auto* page = new QWidget;
    auto* layout = new QVBoxLayout(page);
    auto* exportButton = new QPushButton("Export CSV, TXT, Faculty, Classroom, and Comfort Reports");
    exportButton->setMinimumHeight(48);
    auto* info = new QLabel("Reports are written to the reports folder.");
    layout->addWidget(exportButton);
    layout->addWidget(info);
    layout->addStretch();
    connect(exportButton, &QPushButton::clicked, this, [this]() { exportReports(); });
    return page;
}

void MainWindow::refreshAll()
{
    refreshFacultyTable();
    refreshSubjectTable();
    refreshRoomTable();
    refreshBatchTable();
    refreshDashboard();
    refreshTimetable();
    refreshClashes();
}

void MainWindow::refreshDashboard()
{
    const auto summary = analytics_.analyze(data_.faculty, data_.rooms, data_.batches, data_.timetable);
    utilizationLabel_->setText(QString("Classroom utilization\n%1%").arg(summary.classroomUtilization, 0, 'f', 1));
    workloadLabel_->setText(QString("Faculty workload\n%1%").arg(summary.averageFacultyWorkload, 0, 'f', 1));
    comfortLabel_->setText(QString("Student comfort score\n%1/100").arg(summary.studentComfortScore));
    clashLabel_->setText(QString("Clash statistics\n%1 detected").arg(summary.totalClashes));

    facultyGraph_->setRowCount(static_cast<int>(data_.faculty.size()));
    for (int i = 0; i < static_cast<int>(data_.faculty.size()); ++i) {
        const auto& f = data_.faculty[i];
        const int hours = static_cast<int>(data_.timetable.entriesForFaculty(f.id()).size());
        const int pct = f.maxHoursPerWeek() == 0 ? 0 : (hours * 100 / f.maxHoursPerWeek());
        facultyGraph_->setItem(i, 0, item(qs(f.name())));
        facultyGraph_->setItem(i, 1, item(QString::number(hours)));
        auto* bar = new QProgressBar;
        bar->setRange(0, 100);
        bar->setValue(pct);
        facultyGraph_->setCellWidget(i, 2, bar);
    }

    roomGraph_->setRowCount(static_cast<int>(data_.rooms.size()));
    for (int i = 0; i < static_cast<int>(data_.rooms.size()); ++i) {
        const auto& room = data_.rooms[i];
        const int hours = static_cast<int>(data_.timetable.entriesForRoom(room.roomNumber()).size());
        const int pct = Timetable::Days * (Timetable::Slots - 1) == 0 ? 0 : (hours * 100 / (Timetable::Days * (Timetable::Slots - 1)));
        roomGraph_->setItem(i, 0, item(qs(room.roomNumber())));
        roomGraph_->setItem(i, 1, item(QString::number(hours)));
        auto* bar = new QProgressBar;
        bar->setRange(0, 100);
        bar->setValue(pct);
        roomGraph_->setCellWidget(i, 2, bar);
    }
}

void MainWindow::refreshFacultyTable()
{
    const QString query = facultySearch_ ? facultySearch_->text().trimmed().toLower() : "";
    facultyTable_->setRowCount(0);
    for (const auto& f : data_.faculty) {
        const QString haystack = (qs(f.id()) + qs(f.name()) + qs(f.department())).toLower();
        if (!query.isEmpty() && !haystack.contains(query)) {
            continue;
        }
        const int row = facultyTable_->rowCount();
        facultyTable_->insertRow(row);
        facultyTable_->setItem(row, 0, item(qs(f.id())));
        facultyTable_->setItem(row, 1, item(qs(f.name())));
        facultyTable_->setItem(row, 2, item(qs(f.department())));
        facultyTable_->setItem(row, 3, item(qs(joinList(f.subjects()))));
        facultyTable_->setItem(row, 4, item(QString::number(f.maxHoursPerWeek())));
        facultyTable_->setItem(row, 5, item(QString::number(f.leaveCount())));
    }
}

void MainWindow::refreshSubjectTable()
{
    subjectTable_->setRowCount(static_cast<int>(data_.subjects.size()));
    for (int i = 0; i < static_cast<int>(data_.subjects.size()); ++i) {
        const auto& s = data_.subjects[i];
        subjectTable_->setItem(i, 0, item(qs(s.code())));
        subjectTable_->setItem(i, 1, item(qs(s.name())));
        subjectTable_->setItem(i, 2, item(QString::number(s.weeklyHours())));
        subjectTable_->setItem(i, 3, item(qs(toString(s.type()))));
        subjectTable_->setItem(i, 4, item(qs(s.assignedFacultyId())));
        subjectTable_->setItem(i, 5, item(QString::number(s.difficulty())));
    }
}

void MainWindow::refreshRoomTable()
{
    roomTable_->setRowCount(static_cast<int>(data_.rooms.size()));
    for (int i = 0; i < static_cast<int>(data_.rooms.size()); ++i) {
        const auto& r = data_.rooms[i];
        roomTable_->setItem(i, 0, item(qs(r.roomNumber())));
        roomTable_->setItem(i, 1, item(QString::number(r.capacity())));
        roomTable_->setItem(i, 2, item(qs(toString(r.type()))));
        roomTable_->setItem(i, 3, item(r.available() ? "Available" : "Unavailable"));
    }
}

void MainWindow::refreshBatchTable()
{
    batchTable_->setRowCount(static_cast<int>(data_.batches.size()));
    timetableBatchCombo_->blockSignals(true);
    timetableBatchCombo_->clear();
    for (int i = 0; i < static_cast<int>(data_.batches.size()); ++i) {
        const auto& b = data_.batches[i];
        batchTable_->setItem(i, 0, item(qs(b.id())));
        batchTable_->setItem(i, 1, item(QString::number(b.semester())));
        batchTable_->setItem(i, 2, item(qs(b.section())));
        batchTable_->setItem(i, 3, item(QString::number(b.studentCount())));
        timetableBatchCombo_->addItem(qs(b.id()));
    }
    timetableBatchCombo_->blockSignals(false);
}

void MainWindow::refreshTimetable()
{
    if (!timetableTable_) {
        return;
    }
    timetableTable_->clearContents();
    const std::string batchId = timetableBatchCombo_->currentText().toStdString();
    for (const auto& e : data_.timetable.entriesForBatch(batchId)) {
        QString text = e.breakSlot ? "Lunch Break" : QString("%1\n%2\n%3").arg(qs(e.subjectName), qs(e.facultyId), qs(e.roomNumber));
        auto* tableItem = item(text);
        if (e.breakSlot) {
            tableItem->setBackground(QColor("#fef3c7"));
        } else if (e.fixed) {
            tableItem->setBackground(QColor("#e0e7ff"));
        } else if (e.subjectType == SubjectType::Lab) {
            tableItem->setBackground(QColor("#dcfce7"));
        } else {
            tableItem->setBackground(QColor("#dbeafe"));
        }
        timetableTable_->setItem(e.slot, e.day, tableItem);
    }
}

void MainWindow::refreshClashes()
{
    const auto clashes = ClashDetector().detect(data_.timetable);
    clashTable_->setRowCount(static_cast<int>(clashes.size()));
    for (int i = 0; i < static_cast<int>(clashes.size()); ++i) {
        clashTable_->setItem(i, 0, item(qs(clashes[i].type)));
        clashTable_->setItem(i, 1, item(qs(clashes[i].message)));
        clashTable_->setItem(i, 2, item(qs(clashes[i].suggestion)));
    }
}

void MainWindow::saveData()
{
    try {
        repository_.saveAll(data_);
        statusBar()->showMessage("Auto saved data.", 2500);
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Save Failed", ex.what());
    }
}

void MainWindow::addFaculty()
{
    FacultyDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        data_.faculty.emplace_back(ss(dialog.id->text()), ss(dialog.name->text()), ss(dialog.dept->text()),
                                   splitList(ss(dialog.subjects->text())), dialog.maxHours->value(), dialog.leaves->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::editFaculty()
{
    const int row = selectedRow(facultyTable_);
    if (row < 0) {
        return;
    }
    const std::string id = ss(facultyTable_->item(row, 0)->text());
    auto it = std::find_if(data_.faculty.begin(), data_.faculty.end(), [&](const Faculty& f) { return f.id() == id; });
    if (it == data_.faculty.end()) {
        return;
    }
    FacultyDialog dialog(this, &(*it));
    if (dialog.exec() == QDialog::Accepted) {
        it->setName(ss(dialog.name->text()));
        it->setDepartment(ss(dialog.dept->text()));
        it->setSubjects(splitList(ss(dialog.subjects->text())));
        it->setMaxHoursPerWeek(dialog.maxHours->value());
        it->setLeaveCount(dialog.leaves->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::deleteFaculty()
{
    const int row = selectedRow(facultyTable_);
    if (row < 0) {
        return;
    }
    const std::string id = ss(facultyTable_->item(row, 0)->text());
    data_.faculty.erase(std::remove_if(data_.faculty.begin(), data_.faculty.end(), [&](const Faculty& f) { return f.id() == id; }), data_.faculty.end());
    saveData();
    refreshAll();
}

void MainWindow::addSubject()
{
    SubjectDialog dialog(this, data_.faculty);
    if (dialog.exec() == QDialog::Accepted) {
        data_.subjects.emplace_back(ss(dialog.code->text()), ss(dialog.name->text()), dialog.hours->value(),
                                    subjectTypeFromString(ss(dialog.type->currentText())),
                                    ss(dialog.faculty->currentData().toString()), dialog.difficulty->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::editSubject()
{
    const int row = selectedRow(subjectTable_);
    if (row < 0) {
        return;
    }
    const std::string code = ss(subjectTable_->item(row, 0)->text());
    auto it = std::find_if(data_.subjects.begin(), data_.subjects.end(), [&](const Subject& s) { return s.code() == code; });
    if (it == data_.subjects.end()) {
        return;
    }
    SubjectDialog dialog(this, data_.faculty, &(*it));
    if (dialog.exec() == QDialog::Accepted) {
        it->setName(ss(dialog.name->text()));
        it->setWeeklyHours(dialog.hours->value());
        it->setType(subjectTypeFromString(ss(dialog.type->currentText())));
        it->setAssignedFacultyId(ss(dialog.faculty->currentData().toString()));
        it->setDifficulty(dialog.difficulty->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::deleteSubject()
{
    const int row = selectedRow(subjectTable_);
    if (row < 0) {
        return;
    }
    const std::string code = ss(subjectTable_->item(row, 0)->text());
    data_.subjects.erase(std::remove_if(data_.subjects.begin(), data_.subjects.end(), [&](const Subject& s) { return s.code() == code; }), data_.subjects.end());
    saveData();
    refreshAll();
}

void MainWindow::addRoom()
{
    RoomDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        data_.rooms.emplace_back(ss(dialog.room->text()), dialog.capacity->value(), roomTypeFromString(ss(dialog.type->currentText())), dialog.available->isChecked());
        saveData();
        refreshAll();
    }
}

void MainWindow::editRoom()
{
    const int row = selectedRow(roomTable_);
    if (row < 0) {
        return;
    }
    const std::string room = ss(roomTable_->item(row, 0)->text());
    auto it = std::find_if(data_.rooms.begin(), data_.rooms.end(), [&](const Classroom& r) { return r.roomNumber() == room; });
    if (it == data_.rooms.end()) {
        return;
    }
    RoomDialog dialog(this, &(*it));
    if (dialog.exec() == QDialog::Accepted) {
        it->setCapacity(dialog.capacity->value());
        it->setType(roomTypeFromString(ss(dialog.type->currentText())));
        it->setAvailable(dialog.available->isChecked());
        saveData();
        refreshAll();
    }
}

void MainWindow::deleteRoom()
{
    const int row = selectedRow(roomTable_);
    if (row < 0) {
        return;
    }
    const std::string room = ss(roomTable_->item(row, 0)->text());
    data_.rooms.erase(std::remove_if(data_.rooms.begin(), data_.rooms.end(), [&](const Classroom& r) { return r.roomNumber() == room; }), data_.rooms.end());
    saveData();
    refreshAll();
}

void MainWindow::addBatch()
{
    BatchDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        data_.batches.emplace_back(ss(dialog.id->text()), dialog.semester->value(), ss(dialog.section->text()), dialog.count->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::editBatch()
{
    const int row = selectedRow(batchTable_);
    if (row < 0) {
        return;
    }
    const std::string id = ss(batchTable_->item(row, 0)->text());
    auto it = std::find_if(data_.batches.begin(), data_.batches.end(), [&](const Batch& b) { return b.id() == id; });
    if (it == data_.batches.end()) {
        return;
    }
    BatchDialog dialog(this, &(*it));
    if (dialog.exec() == QDialog::Accepted) {
        it->setSemester(dialog.semester->value());
        it->setSection(ss(dialog.section->text()));
        it->setStudentCount(dialog.count->value());
        saveData();
        refreshAll();
    }
}

void MainWindow::deleteBatch()
{
    const int row = selectedRow(batchTable_);
    if (row < 0) {
        return;
    }
    const std::string id = ss(batchTable_->item(row, 0)->text());
    data_.batches.erase(std::remove_if(data_.batches.begin(), data_.batches.end(), [&](const Batch& b) { return b.id() == id; }), data_.batches.end());
    saveData();
    refreshAll();
}

void MainWindow::generateTimetable()
{
    data_.timetable = scheduler_.generate(data_.faculty, data_.subjects, data_.rooms, data_.batches, data_.fixedSlots);
    saveData();
    refreshAll();
    QMessageBox::information(this, "Timetable Generated", "Optimized timetable generated with clash detection and student wellness scoring.");
}

void MainWindow::exportReports()
{
    try {
        const auto summary = analytics_.analyze(data_.faculty, data_.rooms, data_.batches, data_.timetable);
        const auto clashes = ClashDetector().detect(data_.timetable);
        reportManager_.exportTimetableCsv(data_.timetable);
        reportManager_.exportTimetableTxt(data_.timetable);
        reportManager_.exportFacultyReport(data_.faculty, data_.timetable);
        reportManager_.exportClassroomReport(data_.rooms, data_.timetable);
        reportManager_.exportStudentComfortReport(summary.studentComfortScore, clashes);
        QMessageBox::information(this, "Reports Exported", "All reports were generated in the reports folder.");
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Export Failed", ex.what());
    }
}

void MainWindow::changePassword()
{
    const QString oldPassword = QInputDialog::getText(this, "Change Password", "Old password", QLineEdit::Password);
    if (oldPassword.isNull()) {
        return;
    }
    const QString newPassword = QInputDialog::getText(this, "Change Password", "New password", QLineEdit::Password);
    if (newPassword.isNull()) {
        return;
    }
    try {
        repository_.changePassword(ss(oldPassword), ss(newPassword));
        QMessageBox::information(this, "Password Changed", "Admin password updated.");
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Password Error", ex.what());
    }
}

void MainWindow::backupData()
{
    try {
        QDir().mkpath("backup");
        QDir dataDir("data");
        const auto files = dataDir.entryInfoList(QDir::Files);
        for (const QFileInfo& info : files) {
            const QString destination = QDir("backup").filePath(info.fileName());
            if (QFile::exists(destination)) {
                QFile::remove(destination);
            }
            QFile::copy(info.absoluteFilePath(), destination);
        }
        QMessageBox::information(this, "Backup Complete", "Data backup created in the backup folder.");
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Backup Failed", ex.what());
    }
}

void MainWindow::restoreData()
{
    try {
        QDir().mkpath("data");
        QDir backupDir("backup");
        const auto files = backupDir.entryInfoList(QDir::Files);
        for (const QFileInfo& info : files) {
            const QString destination = QDir("data").filePath(info.fileName());
            if (QFile::exists(destination)) {
                QFile::remove(destination);
            }
            QFile::copy(info.absoluteFilePath(), destination);
        }
        data_ = repository_.loadAll();
        refreshAll();
        QMessageBox::information(this, "Restore Complete", "Backup restored.");
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Restore Failed", ex.what());
    }
}

void MainWindow::applyTheme(bool dark)
{
    if (dark) {
        qApp->setStyleSheet(
            "QMainWindow, QWidget { background:#111827; color:#e5e7eb; font-size:13px; }"
            "#navigation { background:#0f172a; } #navTitle { font-size:22px; font-weight:700; padding:20px; }"
            "#pageTitle { font-size:24px; font-weight:700; margin:8px; }"
            "QPushButton { background:#2563eb; color:white; border:0; border-radius:6px; padding:8px 12px; }"
            "QPushButton:hover { background:#1d4ed8; }"
            "QLineEdit, QComboBox, QSpinBox, QTableWidget { background:#1f2937; color:#f9fafb; border:1px solid #374151; }"
            "QHeaderView::section { background:#374151; color:#f9fafb; padding:6px; border:0; }");
    } else {
        qApp->setStyleSheet(
            "QMainWindow, QWidget { background:#f8fafc; color:#111827; font-size:13px; }"
            "#navigation { background:#0f172a; color:white; } #navTitle { color:white; font-size:22px; font-weight:700; padding:20px; }"
            "#pageTitle { font-size:24px; font-weight:700; margin:8px; }"
            "QPushButton { background:#2563eb; color:white; border:0; border-radius:6px; padding:8px 12px; }"
            "QPushButton:hover { background:#1d4ed8; }"
            "QLineEdit, QComboBox, QSpinBox { background:white; border:1px solid #cbd5e1; border-radius:4px; padding:6px; }"
            "QTableWidget { background:white; gridline-color:#e5e7eb; border:1px solid #cbd5e1; }"
            "QHeaderView::section { background:#e2e8f0; color:#111827; padding:6px; border:0; }");
    }
}
