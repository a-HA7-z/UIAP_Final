#ifndef ADMINLOGINPAGE_H
#define ADMINLOGINPAGE_H

#include <QWidget>

namespace Ui {
class AdminLoginPage;
}

class AdminLoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdminLoginPage(QWidget *parent = nullptr);
    ~AdminLoginPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AdminLoginPage *ui;
};

#endif // ADMINLOGINPAGE_H
