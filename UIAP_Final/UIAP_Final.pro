QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ..

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminentry.cpp \
    adminloginpage.cpp \
    adminsignup.cpp \
    main.cpp \
    firstpage.cpp \
    ../User.cpp \
    ../Admin.cpp \
    ../Costumer.cpp \
    ../BankAccount.cpp \
    ../CurrentAccount.cpp \
    ../DepositAccount.cpp \
    ../GharzolhasanehAccount.cpp \
    projectdata.cpp

HEADERS += \
    adminentry.h \
    adminloginpage.h \
    adminsignup.h \
    firstpage.h \
    ../User.h \
    ../Admin.h \
    ../Costumer.h \
    ../BankAccount.h \
    ../CurrentAccount.h \
    ../DepositAccount.h \
    ../GharzolhasanehAccount.h \
    ../CNode.h \
    ../CLinkedList.h \
    projectdata.h

FORMS += \
    adminentry.ui \
    adminloginpage.ui \
    adminsignup.ui \
    firstpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
