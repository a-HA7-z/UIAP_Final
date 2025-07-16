#include <QMessageBox>
#include "adminloginpage.h"
#include "ui_adminloginpage.h"
#include "projectdata.h"
#include "adminpanel.h"
AdminLoginPage::AdminLoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminLoginPage)
{
    ui->setupUi(this);
}

AdminLoginPage::~AdminLoginPage()
{
    delete ui;
}

void AdminLoginPage::on_pushButton_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this,"Warning","You must fill in all the fields.");
        return;
    }

    Admin* admin = ProjectData::data().findAdmin(username.toStdString());
    if (admin != nullptr)
    {
        if (admin->getPassword() == password.toStdString()) {
            QMessageBox::information(this, "Welcome:)", "Welcome "+QString::fromStdString(admin->getFirstName()));

        }
        else {
            QMessageBox::critical(this, "Login Failed", "Incorrect password.");
            return;
        }
    }
    else {
        QMessageBox::critical(this, "Login Failed", "Username not found!");
        return;
    }

    AdminPanel* panel = new AdminPanel(admin);
    panel->show();
    this->close();
}

