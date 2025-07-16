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
    void loadAdmins();
    ~AdminPanel();

private:
    Ui::AdminPanel *ui;
    Admin* admin;

private slots:
    void on_AdminOptions_itemClicked(QListWidgetItem* item);
    void openCostumerDetailsPage(QListWidgetItem* item);
    void on_AdminOptions_rowChanged(int index);
    void on_showInfoButton_clicked();
    void on_pushButton_clicked();
};

#endif // ADMINPANEL_H
