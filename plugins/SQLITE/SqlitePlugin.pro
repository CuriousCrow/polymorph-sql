#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql widgets


CONFIG += plugin
CONFIG += c++11

TARGET = SqlitePlugin
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
  objects/sqlitedatabase.cpp \
  objects/sqlitefolderitem.cpp \
  objects/sqlitetable.cpp \
  objects/sqliteview.cpp \
  sqliteplugin.cpp

HEADERS  += \
  objects/sqlitedatabase.h \
  objects/sqlitefolderitem.h \
  objects/sqlitetable.h \
  objects/sqliteview.h \
  sqliteplugin.h \
  sqliteconst.h

#FORMS    += \

DISTFILES += SqlitePlugin.json

TRANSLATIONS += \
  translations/sqliteplugin_ru.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

