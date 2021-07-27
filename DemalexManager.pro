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
#DEFINES += SINGLEAPP

SOURCES += main.cpp\
    addnewqueryeditoraction.cpp \
    dropitemobjectaction.cpp \
    exportddltoclipboardaction.cpp \
    exportdmltoclipboardaction.cpp \
    reloadfolderitemsaction.cpp \
    showcreateformaction.cpp \
    showdatabaseexporteditoraction.cpp \
#    testmodule.cpp \
    showitemeditoraction.cpp \
    showsettingsformaction.cpp \
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
    addnewqueryeditoraction.h \
    dropitemobjectaction.h \
    exportddltoclipboardaction.h \
    exportdmltoclipboardaction.h \
    forms/databaseexportform.h \
    reloadfolderitemsaction.h \
    showcreateformaction.h \
    showdatabaseexporteditoraction.h \
#    testmodule.h \
    showitemeditoraction.h \
    showsettingsformaction.h \
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
    sdk/icons.qrc

include(sdk/sdk.pri)

#Add your plugin pri-files here
contains(DEFINES, SINGLEAPP) {
    include(plugins/SQLITE/SqlitePlugin.pri)
    include(plugins/MYSQL/MysqlPlugin.pri)
    include(plugins/POSTGRES/PostgresPlugin.pri)
    include(plugins/FIREBIRD/FirebirdPlugin.pri)
}
