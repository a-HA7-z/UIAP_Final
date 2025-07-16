#include "costumerpanel.h"
#include "ui_costumerpanel.h"

CostumerPanel::CostumerPanel(Costumer* currentCostumer,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CostumerPanel) , costumer(currentCostumer)
{
    ui->setupUi(this);

    connect(ui->CostumerOptions, &QListWidget::currentRowChanged,ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(ui->CostumerOptions, &QListWidget::currentRowChanged, this, &CostumerPanel::on_CostumerOptions_currentRowChanged);
}

void CostumerPanel::on_CostumerOptions_currentRowChanged(int index)
{
    QListWidgetItem* item = ui->CostumerOptions->item(index);
    if (item) {
        on_CostumerOptions_itemClicked(item);
    }
}


CostumerPanel::~CostumerPanel()
{
    delete ui;
}

void CostumerPanel::on_CostumerOptions_itemClicked(QListWidgetItem *item)
{
    QString text = item->text();

    if(text == "My Bank Accounts"){
        ui->stackedWidget->setCurrentWidget(ui->MyBankAccounts);
        loadMyAccounts();
    }
}

void CostumerPanel::loadMyAccounts(){
    ui->myAccountsList->clear();

    const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    while (current != nullptr) {
        std::shared_ptr<BankAccount> account = current->getData();

        QString line1 = QString::fromStdString(
            "Type: " + account->showType() + " | Card Number: " + account->getCardNumber()
            );

        QString line2 = QString::fromStdString(
            "Account Number: " + account->getAccountNumber() +
            " | IBAN: " + account->getIBANNumber() +
            " | CVV2: " + account->getCVV2() +
            " | Exp Date: " + account->getExpDate()
            );

        QString line3 = QString::fromStdString(
            "PIN: " + account->getPIN() +
            " | Static Password: " + account->getStaticPassword() +
            " | Balance: " + std::to_string(account->getBalance())
            );

        ui->myAccountsList->addItem(line1);
        ui->myAccountsList->addItem(line2);
        ui->myAccountsList->addItem(line3);
        if (current->getNext() != nullptr)
            ui->myAccountsList->addItem("----------------------------");

        current = current->getNext();
    }
}

