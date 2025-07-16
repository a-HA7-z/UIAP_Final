#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "firstpage.h"
#include "adminentry.h"
#include "projectdata.h"
#include "admin_costumerdetails.h"
AdminPanel::AdminPanel(Admin* currentAdmin,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminPanel) , admin(currentAdmin)
{
    ui->setupUi(this);    

    QMenuBar* menuBar = new QMenuBar(this);


    QMenu* systemMenu = new QMenu("System", this);


    QAction* logoutAction = new QAction("Logout", this);
    connect(logoutAction, &QAction::triggered, this, [=]() {
        AdminEntry* login = new AdminEntry();
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

    connect(ui->AdminOptions, &QListWidget::currentRowChanged,ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(ui->CostumersList, &QListWidget::itemClicked, this, &AdminPanel::openCostumerDetailsPage);

    connect(ui->AdminOptions, &QListWidget::currentRowChanged, this, &AdminPanel::on_AdminOptions_rowChanged);

}

static const QRegularExpression onlyDigits("[^0-9]");

void AdminPanel::on_AdminOptions_rowChanged(int index)
{
    QListWidgetItem* item = ui->AdminOptions->item(index);
    if (item) {
        on_AdminOptions_itemClicked(item);
    }
}

void AdminPanel::loadCostumers()
{
    ui->CostumersList->clear();

    CNode<Costumer>* current = ProjectData::data().getCostumers().getHead();
    while (current != nullptr) {
        Costumer customer = current->getData();
        QString displayText = QString::fromStdString(
            "Username: " +customer.getUsername() + " | First name: "
            + customer.getFirstName() + " | Last name: " +
            customer.getLastName() );

        ui->CostumersList->addItem(displayText);
        current = current->getNext();
    }
}

void AdminPanel::on_AdminOptions_itemClicked(QListWidgetItem* item)
{
    QString text = item->text();

    if (text == "All Costumers") {
        ui->stackedWidget->setCurrentWidget(ui->pageShowCostumers);
        loadCostumers();
    }

    if(text == "All Bank Accounts"){
        ui->stackedWidget->setCurrentWidget(ui->allBankAccounts);
        loadBankAccounts();
    }

    if(text == "Other Admins"){
        ui->stackedWidget->setCurrentWidget(ui->otherAdminsPage);
        loadAdmins();
    }

    if(text == "Search Bank Account"){
        ui->stackedWidget->setCurrentWidget(ui->SearchBankAccount);
    }

    if(text == "Add Costumer"){
        ui->stackedWidget->setCurrentWidget(ui->addCostumerPage);
    }

    if(text == "Remove Costumer"){
        ui->stackedWidget->setCurrentWidget(ui->RemoveCostumerPage);
    }

    if(text == "Edit my Info"){
        ui->stackedWidget->setCurrentWidget(ui->EditMyInfo);
        loadAdminInfo();
    }
}

void AdminPanel::openCostumerDetailsPage(QListWidgetItem* item)
{
    QString username = item->text().split(" ").at(1);
    Costumer* selected = ProjectData::data().findCostumer(username.toStdString());

    if (selected) {
        Admin_CostumerDetails* detailsPage = new Admin_CostumerDetails(admin);
        detailsPage->setCostumer(selected);
        this->close();
        detailsPage->show();
    }
}

void AdminPanel::loadBankAccounts(){
    ui->AccountsList->clear();

    CLinkedList<std::shared_ptr<BankAccount>>& accounts = ProjectData::data().getBankAccounts();
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

void AdminPanel::loadAdmins(){
    ui->AdminsList->clear();

    CLinkedList<Admin>& admins = ProjectData::data().getAdmins();
    CNode<Admin>* current = admins.getHead();

    while (current != nullptr) {
        Admin anotherAdmin = current->getData();
        if(anotherAdmin.getUsername() == admin->getUsername()){
            current = current->getNext();
            continue;
        }

        QString content = QString::fromStdString(
            "First name: " + anotherAdmin.getFirstName() + " | Last name: " + anotherAdmin.getLastName()
            + " | Age: ");
        content += QString::number(anotherAdmin.getAge());
        ui->AdminsList->addItem(content);
        current = current->getNext();
    }
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_showInfoButton_clicked()
{
    QString cardNumber = ui->cardNumberEdit->text().trimmed();

    if (cardNumber.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a card number.");
        return;
    }

    CNode<Costumer>* current = ProjectData::data().getCostumers().getHead();
    bool found = false;

    while (current != nullptr) {
        Costumer& customer = current->getData();
        CNode<std::shared_ptr<BankAccount>>* accNode = customer.getBankAccounts().getHead();

        while (accNode != nullptr) {
            std::shared_ptr<BankAccount> account = accNode->getData();

            if (account->getCardNumber() == cardNumber.toStdString())
            {
                QString ownerText = QString::fromStdString(
                    "Owner: " + customer.getFirstName() + " " +
                    customer.getLastName() + " | Username: " + customer.getUsername()
                    );
                ui->ownerLabel->setText(ownerText);

                QString accInfo = QString::fromStdString(
                    "Type: " + account->showType() +
                    "\nAccount Number: " + account->getAccountNumber() +
                    "\nIBAN: " + account->getIBANNumber() +
                    "\nCVV2: " + account->getCVV2() +
                    "\nExp Date: " + account->getExpDate() +
                    "\nPIN: " + account->getPIN() +
                    "\nStatic Password: " + account->getStaticPassword() +
                    "\nBalance: ");
                accInfo += QString::fromStdString(std::to_string(account->getBalance()));
                ui->accountInfoLabel->setText(accInfo);

                found = true;
                break;
            }

            accNode = accNode->getNext();
        }

        if (found) break;
        current = current->getNext();
    }

    if (!found) {
        QMessageBox::information(this, "Not Found", "No bank account found with this card number.");
        ui->ownerLabel->clear();
        ui->accountInfoLabel->clear();
    }
}


void AdminPanel::on_pushButton_clicked()
{
    QString fName = ui->fNameEdit->text();
    QString lName = ui->lNameEdit->text();
    QString nationalCode = ui->nationalCodeEdit->text();
    QString ageStr = ui->ageEdit->text();
    QString username = ui->userEdit->text();
    QString password = ui->passEdit->text();

    if (fName.isEmpty() || lName.isEmpty() || nationalCode.isEmpty() || ageStr.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "You must fill in all the fields!");
        return;
    }

    if (nationalCode.length() > 10 || nationalCode.contains(onlyDigits)) {
        QMessageBox::warning(this, "Error", "National Code must be numeric and at most 10 digits.");
        return;
    }

    bool ok;
    int age = ageStr.toInt(&ok);
    if (!ok || age <= 0) {
        QMessageBox::warning(this, "Error", "Age must be a valid positive number.");
        return;
    }

    CNode<Costumer>* current = ProjectData::data().getCostumers().getHead();
    while (current != nullptr) {
        if (current->getData().getUsername() == username.toStdString()) {
            QMessageBox::warning(this, "Error", "Username already exists.");
            return;
        }
        current = current->getNext();
    }

    Costumer newCustomer(fName.toStdString(), lName.toStdString(), nationalCode.toStdString(), age);
    newCustomer.setUsername(username.toStdString());
    newCustomer.setPassword(password.toStdString());

    ProjectData::data().getCostumers().listPushBack(newCustomer);

    QMessageBox::information(this, "Success", "Customer added successfully:)");

    ui->fNameEdit->clear();
    ui->lNameEdit->clear();
    ui->nationalCodeEdit->clear();
    ui->ageEdit->clear();
    ui->userEdit->clear();
    ui->passEdit->clear();
}


void AdminPanel::on_checkCostumer_clicked()
{
    QString username = ui->costumerUsername->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter the username.");
        return;
    }

    Costumer* selectedCostumer = ProjectData::data().findCostumer(username.toStdString());

    if (!selectedCostumer) {
        ui->CostumerInfoLabel->setText("Costumer not found!");
        return;
    }

    QString info = QString::fromStdString( "Costumer INFO | Name: " + selectedCostumer->getFirstName() + " " + selectedCostumer->getLastName()
                       + " / National Code: " + selectedCostumer->getNationalCode() + " / Age: ");
    info += QString::number(selectedCostumer->getAge());
    ui->CostumerInfoLabel->setText(info);
}


void AdminPanel::on_removeButton_clicked()
{
    QString username = ui->costumerUsername->text().trimmed();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a username.");
        return;
    }

    CLinkedList<Costumer>& costumerList = ProjectData::data().getCostumers();
    CNode<Costumer>* current = costumerList.getHead();
    int index = 0;

    while (current != nullptr) {
        if (current->getData().getUsername() == username.toStdString()) {

            std::vector<std::string> cardNumbers;
            CLinkedList<std::shared_ptr<BankAccount>>& CBankAccounts = current->getData().getBankAccounts();
            CNode<std::shared_ptr<BankAccount>>* currentBAccount = CBankAccounts.getHead();
            while(currentBAccount != nullptr){
                cardNumbers.push_back(currentBAccount->getData()->getCardNumber());
                currentBAccount = currentBAccount->getNext();
            }

            CLinkedList<std::shared_ptr<BankAccount>>& allAccounts = ProjectData::data().getBankAccounts();
            CNode<std::shared_ptr<BankAccount>>* accountNode = allAccounts.getHead();
            int accIndex = 0;

            int size = cardNumbers.size();
            while (accountNode != nullptr)
            {
                bool shouldDelete = false;
                for (int i = 0;i < size;i++) {
                    if (accountNode->getData()->getCardNumber() == cardNumbers[i]) {
                        shouldDelete = true;
                        break;
                    }
                }

                if (shouldDelete) {
                    allAccounts.deleteNodeAt(accIndex);
                    accountNode = allAccounts.getHead();
                    accIndex = 0;
                    continue;
                }

                accountNode = accountNode->getNext();
                accIndex++;
            }

            admin->deleteCostumer(costumerList, index);

            QMessageBox::information(this, "Success", "Costumer and their bank accounts removed.");
            ui->CostumerInfoLabel->clear();
            ui->costumerUsername->clear();
            return;
        }

        current = current->getNext();
        index++;
    }

    QMessageBox::warning(this, "Error", "Costumer not found.");
}

void AdminPanel::loadAdminInfo()
{
    ui->fNameEdit2->setText(QString::fromStdString(admin->getFirstName()));
    ui->lNameEdit2->setText(QString::fromStdString(admin->getLastName()));
    ui->nationalCodeEdit_2->setText(QString::fromStdString(admin->getNationalCode()));
    ui->ageEdit2->setText(QString::number(admin->getAge()));
    ui->userEdit2->setText(QString::fromStdString(admin->getUsername()));
    ui->passEdit2->setText(QString::fromStdString(admin->getPassword()));
}

void AdminPanel::on_saveChanges_clicked()
{
    bool changed = false;

    QString fName = ui->fNameEdit2->text().trimmed();
    QString lName = ui->lNameEdit2->text().trimmed();
    QString nationalCode = ui->nationalCodeEdit_2->text().trimmed();
    QString ageStr = ui->ageEdit2->text().trimmed();
    QString username = ui->userEdit2->text().trimmed();
    QString password = ui->passEdit2->text().trimmed();

    if (fName != QString::fromStdString(admin->getFirstName())) {
        if (fName.isEmpty()) {
            QMessageBox::warning(this, "Error", "First name cannot be empty.");
            return;
        }
        admin->setFirstName(fName.toStdString());
        changed = true;
    }

    if (lName != QString::fromStdString(admin->getLastName())) {
        if (lName.isEmpty()) {
            QMessageBox::warning(this, "Error", "Last name cannot be empty.");
            return;
        }
        admin->setLastName(lName.toStdString());
        changed = true;
    }

    if (nationalCode != QString::fromStdString(admin->getNationalCode()))
    {
        if (nationalCode.contains(onlyDigits)) {
            QMessageBox::warning(this, "Error", "Invalid national code.");
            return;
        }

        if (nationalCode.isEmpty() || nationalCode.length() > 10 || nationalCode.length() < 10 ) {
            QMessageBox::warning(this, "Error", "Invalid national code.");
            return;
        }
        admin->setNationalCode(nationalCode.toStdString());
        changed = true;
    }

    if (ageStr != QString::number(admin->getAge())) {
        if (ageStr.isEmpty()) {
            QMessageBox::warning(this, "Error", "Age cannot be empty.");
            return;
        }

        bool ok;
        int age = ageStr.toInt(&ok);
        if (!ok || age <= 0) {
            QMessageBox::warning(this, "Error", "Invalid age.");
            return;
        }

        admin->setAge(age);
        changed = true;
    }

    if (username != QString::fromStdString(admin->getUsername())) {
        if (username.isEmpty()) {
            QMessageBox::warning(this, "Error", "Username cannot be empty.");
            return;
        }
        admin->setUsername(username.toStdString());
        changed = true;
    }

    if (password != QString::fromStdString(admin->getPassword())) {
        if (password.isEmpty()) {
            QMessageBox::warning(this, "Error", "Password cannot be empty.");
            return;
        }
        admin->setPassword(password.toStdString());
        changed = true;
    }

    if (changed) {
        QMessageBox::information(this, "Success", "Admin information updated successfully.");
    } else {
        QMessageBox::information(this, "No Changes", "No changes were made.");
    }
}


