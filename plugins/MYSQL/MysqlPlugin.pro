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

DESTDIR = ../../../build-DemalexGroup/$${BUILDTYPE}/plugins

include(../../sdk/sdk.pri)

SOURCES += \
    mysqldatabase.cpp \
    mysqlfolderitem.cpp \
    mysqlplugin.cpp \
    mysqlsequence.cpp \
    mysqltable.cpp


HEADERS  += \
    mysqldatabase.h \
    mysqlfolderitem.h \
    mysqlplugin.h \
    mysqlsequence.h \
    mysqltable.h


#FORMS    += \

TRANSLATIONS += \
    translations/mysqlplugin_ru.ts

DISTFILES += MysqlPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

