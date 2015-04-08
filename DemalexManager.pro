#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectioneditdialog.cpp \
    lsqltreemodel.cpp \
    qdbstructuremodel.cpp \
    tablebrowserwindow.cpp

HEADERS  += mainwindow.h \
    connectioneditdialog.h \
    lsqltreemodel.h \
    qdbstructuremodel.h \
    tablebrowserwindow.h

FORMS    += mainwindow.ui \
    connectioneditdialog.ui \
    tablebrowserwindow.ui

RESOURCES += \
    icons.qrc
