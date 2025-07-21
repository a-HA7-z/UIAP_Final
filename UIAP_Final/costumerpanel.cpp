#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDate>
#include <QRandomGenerator>
#include <QTimer>
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

    QTimer::singleShot(0, this, [this](){
        ui->CostumerOptions->clearSelection();
        ui->stackedWidget->setCurrentWidget(ui->blankPage);
    });

    menuBar->setStyleSheet("QMenuBar { color: black; }");

    ui->CostumerOptions->setCurrentRow(-1);

    ui->stackedWidget->setCurrentWidget(ui->blankPage);

    connect(ui->CostumerOptions, &QListWidget::currentRowChanged, this, &CostumerPanel::on_CostumerOptions_currentRowChanged);

    styleListWidget(ui->CostumerOptions);
    adjustListHeight(ui->CostumerOptions);

    ui->infoLabel->hide();
    ui->destCardInfoLabel->hide();
    ui->cardInfoLabel->hide();
    ui->cardInfoLabel_2->hide();

    ui->label_9->hide();
    ui->PinLineEdit->hide();
    ui->savePinButton->hide();

    ui->label_10->hide();
    ui->staticPassEdit->hide();
    ui->saveStaticPass->hide();
}

void CostumerPanel::on_CostumerOptions_currentRowChanged(int index)
{
    if (index < 0) {
        ui->stackedWidget->setCurrentWidget(ui->blankPage);
        return;
    }

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

    if(text == "Change the SECOND card password"){
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

                ui->infoLabel->show();

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


void CostumerPanel::on_checkCardNumber_2_clicked()
{
    QString cardNumber = ui->cardNumberLineEdit_2->text();

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
                                          "\nCurrent SECOND password: " + targetAccount->getStaticPassword());

    ui->cardInfoLabel_2->setText(info);
    ui->cardInfoLabel_2->show();
    ui->label_10->show();
    ui->staticPassEdit->show();
    ui->saveStaticPass->show();
}


void CostumerPanel::on_saveStaticPass_clicked()
{
    QString cardNumber = ui->cardNumberLineEdit_2->text();
    QString newPass = ui->staticPassEdit->text();

    if (cardNumber.isEmpty() || newPass.isEmpty()) {
        QMessageBox::warning(this, "Error", "Card number and new Password must not be empty.");
        return;
    }

    if (newPass.length() != 4 || newPass.contains(QRegularExpression("[^0-9]"))) {
        QMessageBox::warning(this, "Error", "Second Password must be exactly 4 digits.");
        return;
    }

    const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    bool cardFound = false;
    while (current != nullptr) {
        if (current->getData()->getCardNumber() == cardNumber.toStdString()) {
            cardFound = true;
            current->getData()->setStaticPassword(newPass.toStdString());
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

    globalAccount->setStaticPassword(newPass.toStdString());

    QMessageBox::information(this, "Success", "PIN changed successfully.");

    ui->staticPassEdit->clear();
    ui->cardNumberLineEdit_2->clear();
    ui->cardInfoLabel_2->clear();
    ui->cardInfoLabel_2->hide();
    ui->label_10->hide();
    ui->staticPassEdit->hide();
    ui->saveStaticPass->hide();
}

void CostumerPanel::on_amountEdit_editingFinished()
{
    QString moneyStr = ui->amountEdit->text();

    if (moneyStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the amount first.");
        return;
    }

    bool ok = false;
    int money = moneyStr.toInt(&ok);

    if (!ok || money <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid amount.");
        ui->amountEdit->clear();
        return;
    }

    const int maxSingleTransfer = 3000000;

    if (money > maxSingleTransfer) {
        QMessageBox::warning(this, "Error", "The transfer amount exceeds the single transaction limit of 3,000,000 Toman.");
        ui->amountEdit->clear();
        return;
    }

}

void CostumerPanel::on_originCardEdit_editingFinished()
{
    QString originCard = ui->originCardEdit->text();

    if (originCard.isEmpty()) {
        ui->destCardInfoLabel->clear();
        originAccountForTransfer = nullptr;
        destAccountForTransfer = nullptr;
        return;
    }

    std::shared_ptr<BankAccount> originAccount = nullptr;
    const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumer->getBankAccounts();
    CNode<std::shared_ptr<BankAccount>>* current = accounts.getHead();

    while (current != nullptr) {
        if (current->getData()->getCardNumber() == originCard.toStdString()) {
            originAccount = current->getData();
            break;
        }
        current = current->getNext();
    }

    if (!originAccount) {
        QMessageBox::warning(this, "Error", "The origin card not found.");
        ui->destCardInfoLabel->clear();
        originAccountForTransfer = nullptr;
        destAccountForTransfer = nullptr;
        return;
    }

    // Check card expiration
    QString expDateStr = QString::fromStdString(originAccount->getExpDate());
    QDate currentDate = QDate::currentDate();

    QDate cardExpDate;
    bool parseOK = false;

    if (expDateStr.contains('/')) {
        QStringList parts = expDateStr.split('/');
        if (parts.size() == 2) {
            int month = parts[0].toInt(&parseOK);
            int year = 2000 + parts[1].toInt(&parseOK); // Assuming "25" => 2025
            cardExpDate = QDate(year, month, 1).addMonths(1).addDays(-1); // Last day of exp month
        }
    }

    if (!parseOK || cardExpDate < currentDate) {
        QMessageBox::warning(this, "Error", "This card is expired.");
        ui->destCardInfoLabel->clear();
        originAccountForTransfer = nullptr;
        ui->originCardEdit->clear();
        return;
    }


    originAccountForTransfer = originAccount;
}

void CostumerPanel::on_destinationCardEdit_editingFinished()
{
    ui->destCardInfoLabel->clear();

    if (!originAccountForTransfer) {
        QMessageBox::warning(this, "Error", "Please enter the origin card first.");
        destAccountForTransfer = nullptr;
        return;
    }

    QString destCardNumber = ui->destinationCardEdit->text();

    if (destCardNumber.isEmpty()) {
        return;
    }

    std::shared_ptr<BankAccount> destAccount = ProjectData::data().findBankAccount(destCardNumber.toStdString());

    if (!destAccount) {
        QMessageBox::warning(this, "Error", "Destination card not found!");
        destAccountForTransfer = nullptr;
        return;
    }

    if (destAccount == originAccountForTransfer) {
        QMessageBox::warning(this, "Error", "You cannot transfer to your own card.");
        ui->destinationCardEdit->clear();
        destAccountForTransfer = nullptr;
        return;
    }

    CNode<Costumer>* costumerNode = ProjectData::data().getCostumers().getHead();
    while (costumerNode != nullptr) {
        const CLinkedList<std::shared_ptr<BankAccount>>& accounts = costumerNode->getData().getBankAccounts();
        CNode<std::shared_ptr<BankAccount>>* accountNode = accounts.getHead();
        while (accountNode != nullptr) {
            if (accountNode->getData()->getCardNumber() == destCardNumber.toStdString())
            {
                destAccountForTransfer = accountNode->getData();

                QString fullName = QString::fromStdString(
                    costumerNode->getData().getFirstName() + " " +
                    costumerNode->getData().getLastName()
                    );
                ui->destCardInfoLabel->setText("Receiver: " + fullName);

                ui->destCardInfoLabel->show();

                return;
            }
            accountNode = accountNode->getNext();
        }
        costumerNode = costumerNode->getNext();
    }

    ui->destCardInfoLabel->clear();
    QMessageBox::warning(this, "Error", "Destination card found but owner could not be determined.");
    destAccountForTransfer = nullptr;
}

void CostumerPanel::on_dynamicPassButton_clicked()
{
    if (!originAccountForTransfer) {
        QMessageBox::warning(this, "Error", "Please select a valid origin card first.");
        return;
    }

    int randomPin = QRandomGenerator::global()->bounded(100000, 1000000);
    QString dynamicPin = QString::number(randomPin);

    originAccountForTransfer->setDynamicPassword(dynamicPin.toStdString());

    ui->secondPassEdit->setText(dynamicPin);

    QMessageBox::information(this, "Dynamic PIN", "Your dynamic PIN has been generated.");
}



void CostumerPanel::on_transferButton_clicked()
{
    if (!originAccountForTransfer || !destAccountForTransfer) {
        QMessageBox::warning(this, "Error", "Please make sure both origin and destination cards are set.");
        return;
    }

    QString moneyStr = ui->amountEdit->text();
    QString enteredPassword = ui->secondPassEdit->text();

    if (moneyStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Amount must not be empty.");
        return;
    }
    if (enteredPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Second password must not be empty.");
        return;
    }

    bool ok;
    long long money = moneyStr.toLongLong(&ok);

    if (!ok || money <= 0) {
        QMessageBox::warning(this, "Error", "Please enter a valid amount.");
        return;
    }

    if (money > 3000000) {
        QMessageBox::warning(this, "Error", "You cannot transfer more than 3,000,000.");
        return;
    }

    if (originAccountForTransfer->getTodayTransferAmount() + money > 6000000) {
        QMessageBox::warning(this, "Error", "You have exceeded the daily transfer limit (6 million).");
        return;
    }

    if (money < 100000) {
        if (!originAccountForTransfer->getDynamicPassword().empty())
        {
            if (enteredPassword.toStdString() != originAccountForTransfer->getDynamicPassword()) {
                QMessageBox::warning(this, "Error", "Incorrect dynamic password.");
                return;
            }
        }
        else
        {
            if (enteredPassword.toStdString() != originAccountForTransfer->getStaticPassword()) {
                QMessageBox::warning(this, "Error", "Incorrect static second password.");
                return;
            }
        }
    }
    else {
        if (enteredPassword.toStdString() != originAccountForTransfer->getDynamicPassword()) {
            QMessageBox::warning(this, "Error", "Incorrect dynamic password.");
            return;
        }
    }

    if(money > originAccountForTransfer->getBalance()){
        QMessageBox::warning(this, "Error", "Insufficient card balance!");
        return;
    }

    costumer->cardToCard(originAccountForTransfer->getCardNumber(), destAccountForTransfer.get(), money);

    QMessageBox::information(this, "Success", "Transfer completed successfully.");
    originAccountForTransfer->addToTodayTransfer(money);

    originAccountForTransfer->setDynamicPassword("");
    ui->originCardEdit->clear();
    ui->destinationCardEdit->clear();
    ui->amountEdit->clear();
    ui->secondPassEdit->clear();
    ui->destCardInfoLabel->clear();

    originAccountForTransfer = nullptr;
    destAccountForTransfer = nullptr;
}

void CostumerPanel::styleListWidget(QListWidget* listWidget)
{
    if (!listWidget) return;

    listWidget->setSpacing(4);

    listWidget->setStyleSheet(R"(
        QListWidget {
            border: 1px solid #ccc;
            border-radius: 8px;
            background-color: #f9f9f9;
            padding: 4px;
        }

        QListWidget::item {
            padding: 10px;
            margin: 4px 0;
            border-radius: 6px;
            background-color: #eaf6ff;
            color: black;
        }

        QListWidget::item:selected {
            background-color: #d0eaff;
            color: #000;
        }

        QListWidget::item:hover {
            background-color: #eaf6ff;
        }
    )");
}

void CostumerPanel::adjustListHeight(QListWidget* listWidget)
{
    if (!listWidget || listWidget->count() == 0)
        return;

    int totalHeight = 0;
    int spacing = listWidget->spacing();
    int count = listWidget->count();

    for (int i = 0; i < count; ++i) {
        int rowHeight = listWidget->sizeHintForRow(i);
        if (rowHeight <= 0) rowHeight = 48;
        totalHeight += rowHeight;
    }

    totalHeight += count * spacing;

    totalHeight += 2 * listWidget->frameWidth();

    totalHeight += 2;

    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setFixedHeight(totalHeight);
}
