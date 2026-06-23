#include "mainwindow.h"
#include "storage.h"

#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

class LoginDialog : public QDialog {
    CsvRepository& repository_;
    QLineEdit* passwordEdit_ = nullptr;

public:
    explicit LoginDialog(CsvRepository& repository, QWidget* parent = nullptr)
        : QDialog(parent), repository_(repository)
    {
        setWindowTitle("Admin Login");
        setModal(true);
        resize(360, 160);

        auto* layout = new QVBoxLayout(this);
        auto* title = new QLabel("Smart Classroom Scheduler");
        title->setStyleSheet("font-size: 20px; font-weight: 700;");
        auto* hint = new QLabel("Admin password");
        passwordEdit_ = new QLineEdit;
        passwordEdit_->setEchoMode(QLineEdit::Password);
        passwordEdit_->setPlaceholderText("Default: admin123");

        auto* buttons = new QDialogButtonBox;
        auto* login = buttons->addButton("Login", QDialogButtonBox::AcceptRole);
        buttons->addButton("Exit", QDialogButtonBox::RejectRole);

        layout->addWidget(title);
        layout->addWidget(hint);
        layout->addWidget(passwordEdit_);
        layout->addWidget(buttons);

        connect(login, &QPushButton::clicked, this, [this]() {
            if (repository_.validatePassword(passwordEdit_->text().toStdString())) {
                accept();
            } else {
                QMessageBox::warning(this, "Login Failed", "Invalid admin password.");
            }
        });
        connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Smart Classroom Scheduler");

    CsvRepository loginRepository("data");
    loginRepository.ensureSampleData();
    LoginDialog login(loginRepository);
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }

    MainWindow window;
    window.show();
    return app.exec();
}

