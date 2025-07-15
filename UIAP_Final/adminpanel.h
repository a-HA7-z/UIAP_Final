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
    ~AdminPanel();

private:
    Ui::AdminPanel *ui;
    Admin* admin;

private slots:
    void on_AdminOptions_itemClicked(QListWidgetItem* item);
};

#endif // ADMINPANEL_H
