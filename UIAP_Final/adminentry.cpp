#include "adminentry.h"
#include "ui_adminentry.h"

AdminEntry::AdminEntry(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminEntry)
{
    ui->setupUi(this);
}

AdminEntry::~AdminEntry()
{
    delete ui;
}
