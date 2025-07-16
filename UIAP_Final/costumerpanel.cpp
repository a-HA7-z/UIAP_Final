#include "costumerpanel.h"
#include "ui_costumerpanel.h"

CostumerPanel::CostumerPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CostumerPanel)
{
    ui->setupUi(this);
}

CostumerPanel::~CostumerPanel()
{
    delete ui;
}
