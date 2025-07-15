#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QListWidgetItem>
#include "Admin.h"

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(Admin* currentAdmin,QWidget *parent = nullptr);
    void loadCostumers();
    void loadBankAccounts();
    ~AdminPanel();

private:
    Ui::AdminPanel *ui;
    Admin* admin;

private slots:
    void on_AdminOptions_itemClicked(QListWidgetItem* item);
    void openCostumerDetailsPage(QListWidgetItem* item);
    void on_AdminOptions_rowChanged(int index);
};

#endif // ADMINPANEL_H
