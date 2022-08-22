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

DESTDIR = ../../../build-DemalexGroup/$${BUILDTYPE}/plugins

include(../../sdk/sdk.pri)

SOURCES += \
    firebirddatabase.cpp \
    firebirdfolderitem.cpp \
    firebirdplugin.cpp \
    firebirdprocedure.cpp \
    firebirdprocedureform.cpp \
    firebirdsequence.cpp \
    firebirdtable.cpp \
    firebirdprimarykey.cpp \
    firebirdforeignkey.cpp \
    firebirdtriggerform.cpp \
    firebirduniqueconstraint.cpp \
    firebirdcheckconstraint.cpp \
    firebirdutils.cpp \
    firebirdview.cpp \
    firebirdtrigger.cpp


HEADERS  += \
    firebirddatabase.h \
    firebirdfolderitem.h \
    firebirdplugin.h \
    firebirdprocedure.h \
    firebirdprocedureform.h \
    firebirdsequence.h \
    firebirdtable.h \
    firebirdprimarykey.h \
    firebirdforeignkey.h \
    firebirdtriggerform.h \
    firebirduniqueconstraint.h \
    firebirdcheckconstraint.h \
    firebirdutils.h \
    firebirdview.h \
    firebirdtrigger.h

FORMS += \
  firebirdprocedureform.ui \
  firebirdtriggerform.ui

TRANSLATIONS += \
    translations/firebirdplugin_ru.ts

DISTFILES += \
    FirebirdPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target



