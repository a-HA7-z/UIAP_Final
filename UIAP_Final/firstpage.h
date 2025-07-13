#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class FirstPage;
}
QT_END_NAMESPACE

class FirstPage : public QMainWindow
{
    Q_OBJECT

public:
    FirstPage(QWidget *parent = nullptr);
    ~FirstPage();

private:
    Ui::FirstPage *ui;
};
#endif // FIRSTPAGE_H
