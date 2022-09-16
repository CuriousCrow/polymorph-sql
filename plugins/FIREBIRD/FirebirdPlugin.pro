#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql widgets


CONFIG += plugin
CONFIG += c++11

TARGET = FirebirdPlugin
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
  forms/firebirddomainform.cpp \
  forms/firebirdprocedureform.cpp \
  forms/firebirdtriggerform.cpp \
  objects/firebirddatabase.cpp \
  objects/firebirdfolderitem.cpp \
  objects/firebirdprocedure.cpp \
  objects/firebirdsequence.cpp \
  objects/firebirdtable.cpp \
  objects/firebirdprimarykey.cpp \
  objects/firebirdforeignkey.cpp \
  objects/firebirduniqueconstraint.cpp \
  objects/firebirdcheckconstraint.cpp \
  objects/firebirdview.cpp \
  objects/firebirdtrigger.cpp \
  objects/firebirddomain.cpp \
  firebirdplugin.cpp \
  firebirdutils.cpp \
  firebirdtypeprovider.cpp

HEADERS  += \
  forms/firebirdprocedureform.h \
  forms/firebirdtriggerform.h \
  forms/firebirddomainform.h \
  objects/firebirddomain.h \
  objects/firebirddatabase.h \
  objects/firebirdfolderitem.h \
  objects/firebirdprocedure.h \
  objects/firebirdsequence.h \
  objects/firebirdtable.h \
  objects/firebirdprimarykey.h \
  objects/firebirdforeignkey.h \
  objects/firebirduniqueconstraint.h \
  objects/firebirdcheckconstraint.h \
  objects/firebirdview.h \
  objects/firebirdtrigger.h \
  firebirdplugin.h \
  firebirdutils.h \
  firebirdtypeprovider.h \
  firebirdconst.h

FORMS += \
  forms/firebirdprocedureform.ui \
  forms/firebirdtriggerform.ui \
  forms/firebirddomainform.ui

TRANSLATIONS += \
  translations/firebirdplugin_ru.ts

DISTFILES += \
  FirebirdPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target



