#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include "costumerpanel.h"
#include "ui_costumerpanel.h"
#include "projectdata.h"
#include "firstpage.h"
#include "costumerloginpage.h"

CostumerPanel::CostumerPanel(Costumer* currentCostumer,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CostumerPanel) , costumer(currentCostumer)
{
    ui->setupUi(this);

    QMenuBar* menuBar = new QMenuBar(this);


    QMenu* systemMenu = new QMenu("System", this);


    QAction* logoutAction = new QAction("Logout", this);
    connect(logoutAction, &QAction::triggered, this, [=]() {
        CostumerLoginPage* login = new CostumerLoginPage();
        login->show();
        this->close();
    });

    QAction* changeRoleAction = new QAction("ChangeRole", this);
    connect(changeRoleAction, &QAction::triggered, this, [=]() {
        FirstPage* selectRole = new FirstPage();
        selectRole->show();
        this->close();
    });

    QAction* exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);


    systemMenu->addAction(logoutAction);
    systemMenu->addAction(changeRoleAction);
    systemMenu->addAction(exitAction);


    menuBar->addMenu(systemMenu);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMenuBar(menuBar);
    this->setLayout(layout);

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

    if(text == "All Bank Accounts"){
        ui->stackedWidget->setCurrentWidget(ui->allAccounts);
        loadAllBankAccounts();
    }

    if(text == "Bank Account Search"){
        ui->stackedWidget->setCurrentWidget(ui->AccountSearch);
    }

    if(text == "Card to Card"){
        ui->stackedWidget->setCurrentWidget(ui->cardToCardPage);
    }

    if(text == "Change the FIRST card password"){
        ui->stackedWidget->setCurrentWidget(ui->changePinPage);
    }

    if(text == "Change the Second card password"){
        ui->stackedWidget->setCurrentWidget(ui->changeStaticPass);
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

void CostumerPanel::loadAllBankAccounts()
{
    ui->allBankAccounts->clear();

    CNode<Costumer>* costumerNode = ProjectData::data().getCostumers().getHead();

    while (costumerNode != nullptr) {
        Costumer& costumer = costumerNode->getData();

        QString ownerInfo = QString::fromStdString("Owner: " + costumer.getFirstName() + " " + costumer.getLastName());

        const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer.getBankAccounts();
        CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

        while (current != nullptr) {
            std::shared_ptr<BankAccount> account = current->getData();

            QString line1 = QString::fromStdString(
                "Type: " + account->showType() +
                " | Card Number: " + account->getCardNumber());

            QString line2 = QString::fromStdString(
                "Account Number: " + account->getAccountNumber() +
                " | IBAN: " + account->getIBANNumber());

            ui->allBankAccounts->addItem(ownerInfo);
            ui->allBankAccounts->addItem(line1);
            ui->allBankAccounts->addItem(line2);

            if (current->getNext() != nullptr)
                ui->allBankAccounts->addItem("----------------------------");

            current = current->getNext();
        }

        if (costumerNode->getNext() != nullptr)
            ui->allBankAccounts->addItem("================================");

        costumerNode = costumerNode->getNext();
    }
}



void CostumerPanel::on_searchButton_clicked()
{
    QString cardNumber = ui->cardNumberEdit->text().trimmed();

    if (cardNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the card number.");
        return;
    }

    CNode<Costumer>* costumerNode = ProjectData::data().getCostumers().getHead();

    while (costumerNode != nullptr) {
        Costumer& costumer = costumerNode->getData();

        const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer.getBankAccounts();
        CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

        while (current != nullptr) {
            std::shared_ptr<BankAccount> account = current->getData();

            if (account->getCardNumber() == cardNumber.toStdString()) {
                QString info;
                info += "Owner: " + QString::fromStdString(costumer.getFirstName()) + " "
                        + QString::fromStdString(costumer.getLastName()) + "\n";
                info += "Type: " + QString::fromStdString(account->showType()) + "\n";
                info += "Card Number: " + QString::fromStdString(account->getCardNumber()) + "\n";
                info += "Account Number: " + QString::fromStdString(account->getAccountNumber()) + "\n";
                info += "IBAN: " + QString::fromStdString(account->getIBANNumber());

                ui->infoLabel->setText(info);
                return;
            }

            current = current->getNext();
        }

        costumerNode = costumerNode->getNext();
    }

    ui->infoLabel->setText("Bank account not found.");
}


void CostumerPanel::on_checkCardNumber_clicked()
{
    QString cardNumber = ui->cardNumberLineEdit->text();

    if (cardNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the card number.");
        return;
    }

    const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    std::shared_ptr<BankAccount> targetAccount = nullptr;

    while (current != nullptr) {
        if (current->getData()->getCardNumber() == cardNumber.toStdString()) {
            targetAccount = current->getData();
            break;
        }
        current = current->getNext();
    }

    if (targetAccount == nullptr) {
        QMessageBox::warning(this, "Error", "Card not found!");
        return;
    }

    QString info = QString::fromStdString("Type: " + targetAccount->showType() +
                                "\nAccount Number: " + targetAccount->getAccountNumber() +
                                "\nIBAN: " + targetAccount->getIBANNumber() +
                                "\nCVV2: " + targetAccount->getCVV2() +
                                "\nExp Date: " + targetAccount->getExpDate() +
                                "\nCurrent FIRST password: " + targetAccount->getPIN());

    ui->cardInfoLabel->setText(info);
    ui->cardInfoLabel->show();
    ui->label_9->show();
    ui->PinLineEdit->show();
    ui->savePinButton->show();
}


void CostumerPanel::on_savePinButton_clicked()
{
    QString cardNumber = ui->cardNumberLineEdit->text();
    QString newPin = ui->PinLineEdit->text();

    if (cardNumber.isEmpty() || newPin.isEmpty()) {
        QMessageBox::warning(this, "Error", "Card number and new PIN must not be empty.");
        return;
    }

    if (newPin.length() != 4 || newPin.contains(QRegularExpression("[^0-9]"))) {
        QMessageBox::warning(this, "Error", "PIN must be exactly 4 digits.");
        return;
    }

    const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    bool cardFound = false;
    while (current != nullptr) {
        if (current->getData()->getCardNumber() == cardNumber.toStdString()) {
            cardFound = true;
            current->getData()->setPIN(newPin.toStdString());
            break;
        }
        current = current->getNext();
    }

    if (!cardFound) {
        QMessageBox::warning(this, "Error", "Card not found.");
        return;
    }

    std::shared_ptr<BankAccount> globalAccount = ProjectData::data().findBankAccount(cardNumber.toStdString());

    if (!globalAccount) {
        QMessageBox::warning(this, "Error", "Bank account not found.");
        return;
    }

    globalAccount->setPIN(newPin.toStdString());

    QMessageBox::information(this, "Success", "PIN changed successfully.");

    ui->PinLineEdit->clear();
    ui->cardNumberLineEdit->clear();
    ui->cardInfoLabel->clear();
    ui->cardInfoLabel->hide();
    ui->label_9->hide();
    ui->PinLineEdit->hide();
    ui->savePinButton->hide();
}

