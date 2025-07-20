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
    void loadAllBankAccounts();

private:
    Ui::CostumerPanel *ui;
    Costumer* costumer;
    std::shared_ptr<BankAccount> originAccountForTransfer = nullptr;
    std::shared_ptr<BankAccount> destAccountForTransfer = nullptr;

private slots:
    void on_CostumerOptions_currentRowChanged(int index);
    void on_CostumerOptions_itemClicked(QListWidgetItem *item);
    void on_searchButton_clicked();
    void on_checkCardNumber_clicked();
    void on_savePinButton_clicked();
    void on_checkCardNumber_2_clicked();
    void on_saveStaticPass_clicked();
    void on_destinationCardEdit_editingFinished();
    void on_originCardEdit_editingFinished();
    void on_amountEdit_editingFinished();
    void on_dynamicPassButton_clicked();
    void on_transferButton_clicked();
};

#endif // COSTUMERPANEL_H
