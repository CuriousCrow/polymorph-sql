#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app

CONFIG ~= s/-O[0123s]//g
CONFIG += -O0

RC_ICONS = icons/cc_16.ico

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
#    plugins/FIREBIRD/firebirddatabase.cpp \
#    plugins/FIREBIRD/firebirdfolderitem.cpp \
#    plugins/FIREBIRD/firebirdplugin.cpp \
#    plugins/FIREBIRD/firebirdtable.cpp \
#    plugins/MYSQL/mysqldatabase.cpp \
#    plugins/MYSQL/mysqlfolderitem.cpp \
#    plugins/MYSQL/mysqlplugin.cpp \
#    plugins/MYSQL/mysqltable.cpp \
#    plugins/POSTGRES/postgresfunctionitem.cpp \
#    plugins/POSTGRES/postgresplugin.cpp \
#    plugins/POSTGRES/postgresviewitem.cpp \
#    plugins/SQLITE/sqlitedatabase.cpp \
#    plugins/SQLITE/sqlitefolderitem.cpp \
#    plugins/SQLITE/sqliteplugin.cpp \
#    plugins/SQLITE/sqlitetable.cpp \
#    plugins/SQLITE/sqliteviewitem.cpp \
#    plugins/POSTGRES/postgrestriggeritem.cpp \
#    plugins/POSTGRES/postgrescheckconstraint.cpp \
#    plugins/POSTGRES/postgresdatabase.cpp \
#    plugins/POSTGRES/postgresforeignkey.cpp \
#    plugins/POSTGRES/postgresprimarykey.cpp \
#    plugins/POSTGRES/postgressequence.cpp \
#    plugins/POSTGRES/postgrestable.cpp \
#    plugins/POSTGRES/postgresuniqueconstraint.cpp \
#    plugins/POSTGRES/postgresfolderitem.cpp

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
#    plugins/FIREBIRD/firebirddatabase.h \
#    plugins/FIREBIRD/firebirdfolderitem.h \
#    plugins/FIREBIRD/firebirdplugin.h \
#    plugins/FIREBIRD/firebirdtable.h \
#    plugins/MYSQL/mysqldatabase.h \
#    plugins/MYSQL/mysqlfolderitem.h \
#    plugins/MYSQL/mysqlplugin.h \
#    plugins/MYSQL/mysqltable.h \
#    plugins/POSTGRES/postgresplugin.h \
#    plugins/POSTGRES/postgresviewitem.h \
#    plugins/SQLITE/sqlitedatabase.h \
#    plugins/SQLITE/sqlitefolderitem.h \
#    plugins/SQLITE/sqliteplugin.h \
#    plugins/SQLITE/sqlitetable.h \
#    plugins/SQLITE/sqliteviewitem.h \
#    plugins/POSTGRES/postgrestriggeritem.h \
#    plugins/POSTGRES/postgrescheckconstraint.h \
#    plugins/POSTGRES/postgresdatabase.h \
#    plugins/POSTGRES/postgresforeignkey.h \
#    plugins/POSTGRES/postgresfunctionitem.h \
#    plugins/POSTGRES/postgresprimarykey.h \
#    plugins/POSTGRES/postgressequence.h \
#    plugins/POSTGRES/postgrestable.h \
#    plugins/POSTGRES/postgresuniqueconstraint.h \
#    plugins/POSTGRES/postgresfolderitem.h

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
