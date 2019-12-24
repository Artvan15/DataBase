QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allwaybills.cpp \
    chosecompany.cpp \
    choseworker.cpp \
    companies.cpp \
    deletewaybill.cpp \
    main.cpp \
    connecttobd.cpp \
    mainwindow.cpp \
    office.cpp \
    waybill.cpp

HEADERS += \
    allwaybills.h \
    chosecompany.h \
    choseworker.h \
    companies.h \
    connecttobd.h \
    deletewaybill.h \
    mainwindow.h \
    office.h \
    waybill.h

FORMS += \
    allwaybills.ui \
    chosecompany.ui \
    choseworker.ui \
    companies.ui \
    connecttobd.ui \
    deletewaybill.ui \
    office.ui \
    waybill.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
