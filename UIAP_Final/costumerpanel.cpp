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
    }
}

