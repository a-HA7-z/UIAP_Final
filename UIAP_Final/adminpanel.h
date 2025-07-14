#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include "Admin.h"

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(Admin* currentAdmin,QWidget *parent = nullptr);
    ~AdminPanel();

private:
    Ui::AdminPanel *ui;
    Admin* admin;
};

#endif // ADMINPANEL_H
