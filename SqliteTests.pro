QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
  tests/sqliteunittests.h

SOURCES += \
  tests/sqliteunittests.cpp

DESTDIR = ../../../build-PolymorphGroup/$${BUILDTYPE}/plugins

include(sdk/sdk.pri)
include(plugins/SQLITE/SqlitePlugin.pri)
