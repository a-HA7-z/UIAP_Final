#include "adminentry.h"
#include "ui_adminentry.h"
#include "adminsignup.h"
AdminEntry::AdminEntry(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminEntry)
{
    ui->setupUi(this);
}

AdminEntry::~AdminEntry()
{
    delete ui;
}

void AdminEntry::on_SignupButton_clicked()
{
    this->close();
    AdminSignUp* signUpPage = new AdminSignUp;
    signUpPage->show();
}

