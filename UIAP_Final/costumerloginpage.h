#ifndef COSTUMERLOGINPAGE_H
#define COSTUMERLOGINPAGE_H

#include <QWidget>

namespace Ui {
class CostumerLoginPage;
}

class CostumerLoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit CostumerLoginPage(QWidget *parent = nullptr);
    ~CostumerLoginPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CostumerLoginPage *ui;
};

#endif // COSTUMERLOGINPAGE_H
