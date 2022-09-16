QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
  tests/postgresunittests.h

SOURCES += \
  tests/postgresunittests.cpp

DESTDIR = ../../../build-PolymorphGroup/$${BUILDTYPE}/plugins

include(sdk/sdk.pri)
include(plugins/POSTGRES/PostgresPlugin.pri)
