#include "admin_costumerdetails.h"
#include "ui_admin_costumerdetails.h"
#include "adminpanel.h"

Admin_CostumerDetails::Admin_CostumerDetails(Admin* currentAdmin,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_CostumerDetails)
{
    ui->setupUi(this);
    admin = currentAdmin;
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
    ui->AccountsList->clear();

    CLinkedList<std::shared_ptr<BankAccount>>& accounts = currentCostumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    while (current != nullptr) {
        std::shared_ptr<BankAccount> account = current->getData();

        QString line1 = QString::fromStdString(
            "Type: " + account->showType() + " | Card Number: " + account->getCardNumber() + " | Account Number: " + account->getAccountNumber()
            );

        QString line2 = QString::fromStdString(
            "IBAN: " + account->getIBANNumber() + " | CVV2: " + account->getCVV2() + " | Exp Date: " + account->getExpDate()
            );

        QString line3 = QString::fromStdString(
            "PIN: " + account->getPIN() + " | Static Password: " + account->getStaticPassword() + " | Balance: " + std::to_string(account->getBalance())
            );

        ui->AccountsList->addItem(line1);
        ui->AccountsList->addItem(line2);
        ui->AccountsList->addItem(line3);
        if(current->getNext() != nullptr){
            ui->AccountsList->addItem("--------------------------");
        }
        current = current->getNext();
    }
}



void Admin_CostumerDetails::on_AddBankAcount_clicked()
{
    ui->DetailsStack->setCurrentWidget(ui->pageAddBankAccount);
}


void Admin_CostumerDetails::on_EditInfo_clicked()
{
    ui->DetailsStack->setCurrentWidget(ui->pageEditInfo);
}


void Admin_CostumerDetails::on_pushButton_clicked()
{
    this->close();
    AdminPanel* adminPanel = new AdminPanel(admin);
    adminPanel->show();
}

