#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat widgets


CONFIG += plugin
CONFIG += c++11

TARGET = MysqlPlugin
TEMPLATE = lib

include(../../sdk/sdk.pri)

SOURCES += \
    mysqldatabase.cpp \
    mysqlfolderitem.cpp \
    mysqlplugin.cpp \
    mysqltable.cpp


HEADERS  += \
    mysqldatabase.h \
    mysqlfolderitem.h \
    mysqlplugin.h \
    mysqltable.h


#FORMS    += \

DISTFILES += MysqlPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

