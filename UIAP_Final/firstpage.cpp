#include "firstpage.h"
#include "ui_firstpage.h"
#include "adminentry.h"
#include "costumerloginpage.h"

FirstPage::FirstPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FirstPage)
{
    ui->setupUi(this);   
}

FirstPage::~FirstPage()
{
    delete ui;
}

void FirstPage::on_AdminRole_clicked()
{
    this->close();
    AdminEntry* entry = new AdminEntry;
    entry->show();
}


void FirstPage::on_Costumerrole_clicked()
{
    this->close();
    CostumerLoginPage* loginCostumer = new CostumerLoginPage;
    loginCostumer->show();
}

