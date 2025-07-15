#ifndef ADMIN_COSTUMERDETAILS_H
#define ADMIN_COSTUMERDETAILS_H

#include <QWidget>
#include "projectdata.h"
namespace Ui {
class Admin_CostumerDetails;
}

class Admin_CostumerDetails : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_CostumerDetails(Admin* currentAdmin,QWidget *parent = nullptr);
    void setCostumer(Costumer* costumer);
    ~Admin_CostumerDetails();

private slots:
    void on_BankAccounts_clicked();

    void on_AddBankAcount_clicked();

    void on_EditInfo_clicked();

    void on_pushButton_clicked();

private:
    Ui::Admin_CostumerDetails *ui;
    Costumer* currentCostumer;
    Admin* admin;
};

#endif // ADMIN_COSTUMERDETAILS_H
