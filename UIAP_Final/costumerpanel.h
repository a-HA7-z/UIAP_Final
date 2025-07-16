#ifndef COSTUMERPANEL_H
#define COSTUMERPANEL_H
#include <QListWidgetItem>
#include <QWidget>
#include "Costumer.h"

namespace Ui {
class CostumerPanel;
}

class CostumerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CostumerPanel(Costumer* currentCostumer,QWidget *parent = nullptr);
    ~CostumerPanel();
    void loadMyAccounts();

private:
    Ui::CostumerPanel *ui;
    Costumer* costumer;

private slots:
    void on_CostumerOptions_currentRowChanged(int index);
    void on_CostumerOptions_itemClicked(QListWidgetItem *item);
};

#endif // COSTUMERPANEL_H
