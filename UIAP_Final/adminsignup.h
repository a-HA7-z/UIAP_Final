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

private:
    Ui::AdminSignUp *ui;
};

#endif // ADMINSIGNUP_H
