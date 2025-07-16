#include <QMessageBox>
#include "costumerloginpage.h"
#include "ui_costumerloginpage.h"
#include "projectdata.h"
#include "costumerpanel.h"

CostumerLoginPage::CostumerLoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CostumerLoginPage)
{
    ui->setupUi(this);
}

CostumerLoginPage::~CostumerLoginPage()
{
    delete ui;
}

void CostumerLoginPage::on_pushButton_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this,"Warning","You must fill in all the fields.");
        return;
    }

    Costumer* costumer = ProjectData::data().findCostumer(username.toStdString());
    if (costumer != nullptr)
    {
        if (costumer->getPassword() == password.toStdString()) {
            QMessageBox::information(this, "Welcome:)", "Welcome "+QString::fromStdString(costumer->getFirstName()));
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
    this->close();
    CostumerPanel* panel = new CostumerPanel(costumer);
    panel->show();
}

