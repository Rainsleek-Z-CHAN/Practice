#-------------------------------------------------
#
# Project created by QtCreator 2019-07-07T08:40:18
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += core
QT+=network
DEFINES += QT_NO_WARNING_OUTPUT\
                     QT_NO_DEBUG_OUTPUT
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        addstu.cpp \
        findpasswd.cpp \
        main.cpp \
        mainwindow.cpp \
        mytcpclient.cpp \
        person.cpp \
        sqlite.cpp \
        user.cpp \
        widget.cpp \
    style.cpp

HEADERS += \
        addstu.h \
        findpasswd.h \
        mainwindow.h \
        mytcpclient.h \
        person.h \
        sqlite.h \
        user.h \
        widget.h \
    style.h

FORMS += \
        addstu.ui \
        findpasswd.ui \
        mainwindow.ui \
        mytcpclient.ui \
        person.ui \
        widget.ui \
    style.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    long.qrc

RC_ICONS = myapp.ico

DISTFILES +=
