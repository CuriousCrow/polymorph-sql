#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat widgets


CONFIG += plugin
CONFIG += c++11

TARGET = SqlitePlugin
TEMPLATE = lib

include(../../sdk/sdk.pri)

SOURCES += \
    sqlitedatabase.cpp \
    sqlitefolderitem.cpp \
    sqliteplugin.cpp \
    sqlitetable.cpp \
    sqliteviewitem.cpp

HEADERS  += \
    sqlitedatabase.h \
    sqlitefolderitem.h \
    sqliteplugin.h \
    sqlitetable.h \
    sqliteviewitem.h

#FORMS    += \

DISTFILES += SqlitePlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

