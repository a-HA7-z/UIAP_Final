#include "admin_costumerdetails.h"
#include "ui_admin_costumerdetails.h"

Admin_CostumerDetails::Admin_CostumerDetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_CostumerDetails)
{
    ui->setupUi(this);
}

void Admin_CostumerDetails::setCostumer(Costumer* costumer)
{
    currentCostumer = costumer;
}

Admin_CostumerDetails::~Admin_CostumerDetails()
{
    delete ui;
}

void Admin_CostumerDetails::on_BankAccounts_clicked()
{
    ui->DetailsStack->setCurrentWidget(ui->pageBankAccounts);
}


void Admin_CostumerDetails::on_AddBankAcount_clicked()
{
    ui->DetailsStack->setCurrentWidget(ui->pageAddBankAccount);
}


void Admin_CostumerDetails::on_EditInfo_clicked()
{
    ui->DetailsStack->setCurrentWidget(ui->pageEditInfo);
}

