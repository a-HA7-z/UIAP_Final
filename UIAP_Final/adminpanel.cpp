#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>

#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "firstpage.h"
#include "adminentry.h"
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
}

AdminPanel::~AdminPanel()
{
    delete ui;
}
