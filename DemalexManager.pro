#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app

CONFIG ~= s/-O[0123s]//g
CONFIG += -O0

RC_ICONS = sdk/icons/cc_16.ico

#Use this flag to compile all plugins inside main application
DEFINES += SINGLEAPP

SOURCES += main.cpp\
    forms/mainwindow.cpp \
    forms/tablebrowserwindow.cpp \
    widgets/tablebrowserdelegate.cpp

HEADERS  += \
    forms/mainwindow.h \
    forms/tablebrowserwindow.h \
    widgets/tablebrowserdelegate.h

FORMS    += \
    forms/mainwindow.ui \
    forms/tablebrowserwindow.ui

RESOURCES += \
    sdk/icons.qrc

include(sdk/sdk.pri)

#Add your plugin pri-files here
contains(DEFINES, SINGLEAPP) {
    include(plugins/SQLITE/SqlitePlugin.pri)
    include(plugins/MYSQL/MysqlPlugin.pri)
    include(plugins/POSTGRES/PostgresPlugin.pri)
    include(plugins/FIREBIRD/FirebirdPlugin.pri)
}
