#ifndef ADMINSIGNUP_H
#define ADMINSIGNUP_H

#include <QWidget>

namespace Ui {
class AdminSignUp;
}

class AdminSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit AdminSignUp(QWidget *parent = nullptr);
    ~AdminSignUp();

private slots:
    void on_Username_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_Age_textChanged(const QString &arg1);

    void on_NationalCode_textChanged(const QString &arg1);

    void on_Password_textChanged(const QString &arg1);

private:
    Ui::AdminSignUp *ui;
};

#endif // ADMINSIGNUP_H
