#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T18:54:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyTcpServer
TEMPLATE = app


SOURCES += main.cpp\
        mytcpserver.cpp \
        widget.cpp

HEADERS  += mytcpserver.h \
    widget.h

FORMS    += mytcpserver.ui \
    widget.ui

RC_ICONS = myapp.ico
