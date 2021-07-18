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

RC_ICONS = icons/cc_16.ico

#Use this flag to compile all plugins inside main application
DEFINES += SINGLEAPP

SOURCES += main.cpp\
    widgets/blobeditor.cpp \
    forms/databaseexportform.cpp \
    widgets/itemviewer.cpp \
    forms/queryhistoryform.cpp \
    forms/settingsform.cpp \
    forms/tablebrowserwindow.cpp \
    forms/queryeditorwindow.cpp \
    widgets/lqueryeditor.cpp \
    widgets/tablebrowserdelegate.cpp \
    forms/mainwindow.cpp

HEADERS  += \
    forms/databaseexportform.h \
    widgets/blobeditor.h \
    widgets/itemviewer.h \
    forms/mainwindow.h \
    forms/queryhistoryform.h \
    forms/settingsform.h \
    widgets/tablebrowserdelegate.h \
    forms/tablebrowserwindow.h \
    forms/queryeditorwindow.h \
    widgets/lqueryeditor.h

FORMS    += \
    widgets/itemviewer.ui \
    widgets/blobeditor.ui \
    forms/databaseexportform.ui \
    forms/mainwindow.ui \
    forms/queryhistoryform.ui \
    forms/settingsform.ui \
    forms/tablebrowserwindow.ui \
    forms/queryeditorwindow.ui

RESOURCES += \
    icons.qrc

include(sdk/sdk.pri)

#Add your plugin pri-files here
contains(DEFINES, SINGLEAPP) {
    include(plugins/SQLITE/SqlitePlugin.pri)
    include(plugins/MYSQL/MysqlPlugin.pri)
    include(plugins/POSTGRES/PostgresPlugin.pri)
    include(plugins/FIREBIRD/FirebirdPlugin.pri)
}
