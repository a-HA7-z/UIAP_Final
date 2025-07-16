#include <QRegularExpression>
#include <QMessageBox>
#include "adminsignup.h"
#include "ui_adminsignup.h"
#include "projectdata.h"
#include "adminpanel.h"
AdminSignUp::AdminSignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminSignUp)
{
    ui->setupUi(this);
    ui->ErrorUsername->hide();
    ui->PasswordErrorLabel->hide();
    ui->ageErrorLabel->hide();
    ui->nationalCodeErrorLabel->hide();
    ui->FNameErrorLabel->hide();
    ui->LNameErrorLabel->hide();
}

AdminSignUp::~AdminSignUp()
{
    delete ui;
}

void AdminSignUp::on_Username_textChanged(const QString &arg1)
{
    Admin* ExistingAdmin = ProjectData::data().findAdmin(arg1.toStdString());
    if (ExistingAdmin != nullptr) {
        ui->ErrorUsername->show();
        ui->pushButton->setEnabled(false);
    } else {
        ui->ErrorUsername->hide();
        ui->pushButton->setEnabled(true);
    }
}

void AdminSignUp::on_Password_textChanged(const QString &text)
{
    if (text.length() < 6) {

        ui->PasswordErrorLabel->show();
        ui->pushButton->setEnabled(false);
    } else {
        ui->PasswordErrorLabel->hide();
        ui->pushButton->setEnabled(true);
    }
}

void AdminSignUp::on_Age_textChanged(const QString &text)
{
    bool ok;
    int age = text.toInt(&ok);

    if (!ok || age < 0 || age > 150) {
        ui->ageErrorLabel->show();
        ui->pushButton->setEnabled(false);
    } else {
        ui->ageErrorLabel->hide();
        ui->pushButton->setEnabled(true);
    }
}

void AdminSignUp::on_NationalCode_textChanged(const QString &text)
{
    QRegularExpression re("^\\d{0,10}$");

    if (!re.match(text).hasMatch()) {
        ui->nationalCodeErrorLabel->show();
        ui->pushButton->setEnabled(false);
    }
    else if (text.length() != 10) {
        ui->nationalCodeErrorLabel->show();
        ui->pushButton->setEnabled(false);
    }
    else {
        ui->nationalCodeErrorLabel->hide();
        ui->pushButton->setEnabled(true);
    }
}

void AdminSignUp::on_pushButton_clicked()
{
    if(ui->FName->text().isEmpty()||ui->LName->text().isEmpty()||ui->Username->text().isEmpty()||ui->Password->text().isEmpty()||ui->NationalCode->text().isEmpty()||ui->Age->text().isEmpty())
    {
        if(ui->FName->text().isEmpty()){
            ui->FNameErrorLabel->show();
        }
        if(ui->FName->text().isEmpty()){
            ui->LNameErrorLabel->show();
        }
        else {
            ui->FNameErrorLabel->hide();
            ui->LNameErrorLabel->hide();
        }
        QMessageBox::warning(this, "Warning", "You must fill in all the fields.");
        return;
    }

    Admin newAdmin(ui->FName->text().toStdString(),ui->LName->text().toStdString(),ui->NationalCode->text().toStdString(),ui->Age->text().toInt());

    newAdmin.setUsername(ui->Username->text().toStdString());
    newAdmin.setPassword(ui->Password->text().toStdString());

    ProjectData::data().addAdmin(newAdmin);

    Admin* addedAdmin = ProjectData::data().findAdmin(newAdmin.getUsername());
    if (addedAdmin) {
        AdminPanel* panel = new AdminPanel(addedAdmin);
        panel->show();
        this->close();
    }
}
