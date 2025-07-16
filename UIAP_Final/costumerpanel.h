#ifndef COSTUMERPANEL_H
#define COSTUMERPANEL_H

#include <QWidget>

namespace Ui {
class CostumerPanel;
}

class CostumerPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CostumerPanel(QWidget *parent = nullptr);
    ~CostumerPanel();

private:
    Ui::CostumerPanel *ui;
};

#endif // COSTUMERPANEL_H
