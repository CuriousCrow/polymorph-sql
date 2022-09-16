#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql widgets


CONFIG += plugin
CONFIG += c++11

TARGET = MysqlPlugin
TEMPLATE = lib

CONFIG(debug,debug|release){
    BUILDTYPE = debug
}
else {
    BUILDTYPE = release
}

DESTDIR = ../../../build-PolymorphSqlGroup/$${BUILDTYPE}/plugins

include(../../sdk/sdk.pri)

SOURCES += \
  objects/mysqldatabase.cpp \
  objects/mysqlfolderitem.cpp \
  objects/mysqlview.cpp \
  objects/mysqlprimarykey.cpp \
  objects/mysqlforeignkey.cpp \
  objects/mysqlcheckconstraint.cpp \
  objects/mysqluniqueconstraint.cpp \
  objects/mysqlprocedure.cpp \
  objects/mysqltrigger.cpp \
  objects/mysqlsequence.cpp \
  objects/mysqltable.cpp \
  forms/mysqltriggerform.cpp \
  forms/mysqlprocedureeditform.cpp \
  mysqlplugin.cpp

HEADERS  += \
  objects/mysqldatabase.h \
  objects/mysqlfolderitem.h \
  objects/mysqlsequence.h \
  objects/mysqltable.h \
  objects/mysqlview.h \
  objects/mysqlprimarykey.h \
  objects/mysqlforeignkey.h \
  objects/mysqluniqueconstraint.h \
  objects/mysqlcheckconstraint.h \
  objects/mysqlprocedure.h \
  objects/mysqltrigger.h \
  forms/mysqltriggerform.h \
  forms/mysqlprocedureeditform.h \
  mysqlplugin.h \
  mysqlconst.h

FORMS    += \
  forms/mysqlprocedureeditform.ui \
  forms/mysqltriggerform.ui

TRANSLATIONS += \
  translations/mysqlplugin_ru.ts

DISTFILES += MysqlPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
