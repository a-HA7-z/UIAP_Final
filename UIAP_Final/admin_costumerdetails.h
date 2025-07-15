#ifndef ADMIN_COSTUMERDETAILS_H
#define ADMIN_COSTUMERDETAILS_H

#include <QWidget>

namespace Ui {
class Admin_CostumerDetails;
}

class Admin_CostumerDetails : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_CostumerDetails(QWidget *parent = nullptr);
    ~Admin_CostumerDetails();

private:
    Ui::Admin_CostumerDetails *ui;
};

#endif // ADMIN_COSTUMERDETAILS_H
