#include <QMessageBox>
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
            "Type: " + account->showType() + " | Card Number: " + account->getCardNumber()
            );

        QString line2 = QString::fromStdString(
            "Account Number: " + account->getAccountNumber() + " | IBAN: " + account->getIBANNumber() + " | CVV2: " + account->getCVV2() + " | Exp Date: " + account->getExpDate()
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

    CLinkedList<std::shared_ptr<BankAccount>>& accounts = currentCostumer->getBankAccounts();

    if (accounts.getSize() >= 5) {
        QMessageBox::warning(this, "Error", "This costumer already has 5 bank accounts and cannot have more!");
        return;
    }
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


void Admin_CostumerDetails::on_AddAccountButton_clicked()
{
    QString accNum = ui->AccountNumber->text().trimmed();
    QString iban = ui->IBAN->text().trimmed();
    QString cardNum = ui->CardNumber->text().trimmed();
    QString expDate = ui->ExpDate->text().trimmed();
    QString cvv2 = ui->CVV2->text().trimmed();
    QString pin = ui->CardPIN->text().trimmed();
    QString staticPass = ui->StaticPassword->text().trimmed();
    QString balanceStr = ui->Balance->text().trimmed();

    if (accNum.isEmpty() || iban.isEmpty() || cardNum.isEmpty() || expDate.isEmpty()
        || cvv2.isEmpty() || pin.isEmpty() || staticPass.isEmpty() || balanceStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "You must fill all the fields.");
        return;
    }

    bool ok;
    long long balance = balanceStr.toLongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Balance must be a valid number.");
        return;
    }

    int type = -1;
    if (ui->Current->isChecked()) type = 0;
    else if (ui->Deposite->isChecked()) type = 1;
    else if (ui->Gharz->isChecked()) type = 2;

    if (type == -1) {
        QMessageBox::warning(this, "Error", "Please select a bank account type.");
        return;
    }

    admin->createBankAccount(*currentCostumer, type,
                            cardNum.toStdString(),accNum.toStdString(),
                            iban.toStdString(),cvv2.toStdString(),
                            expDate.toStdString(),pin.toStdString(),
                            staticPass.toStdString(),balance);

    std::shared_ptr<BankAccount> lastCreated = currentCostumer->getBankAccounts().getTail()->getData();
    ProjectData::data().addBankAccount(lastCreated);

    QMessageBox::information(this, "Success", "Bank account successfully created.");

    ui->AccountNumber->clear();
    ui->IBAN->clear();
    ui->CardNumber->clear();
    ui->ExpDate->clear();
    ui->CVV2->clear();
    ui->CardPIN->clear();
    ui->StaticPassword->clear();
    ui->Balance->clear();
}


