#ifndef ADMINENTRY_H
#define ADMINENTRY_H

#include <QWidget>

namespace Ui {
class AdminEntry;
}

class AdminEntry : public QWidget
{
    Q_OBJECT

public:
    explicit AdminEntry(QWidget *parent = nullptr);
    ~AdminEntry();

private:
    Ui::AdminEntry *ui;
};

#endif // ADMINENTRY_H
