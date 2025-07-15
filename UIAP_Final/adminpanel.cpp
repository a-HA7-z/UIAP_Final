#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

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

}

void AdminPanel::loadCostumers()
{
    ui->CostumersList->clear();

    CNode<Costumer>* current = ProjectData::data().getCostumers().getHead();
    while (current != nullptr) {
        Costumer customer = current->getData();
        QString displayText = QString::fromStdString(
            "Username: " +customer.getUsername() + " | "
            + customer.getFirstName() + " " +
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

AdminPanel::~AdminPanel()
{
    delete ui;
}
