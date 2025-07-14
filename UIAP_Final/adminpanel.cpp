#include "adminpanel.h"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(Admin* currentAdmin,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminPanel) , admin(currentAdmin)
{
    ui->setupUi(this);
}

AdminPanel::~AdminPanel()
{
    delete ui;
}
