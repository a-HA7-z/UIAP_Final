#include "adminsignup.h"
#include "ui_adminsignup.h"

AdminSignUp::AdminSignUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminSignUp)
{
    ui->setupUi(this);
}

AdminSignUp::~AdminSignUp()
{
    delete ui;
}
