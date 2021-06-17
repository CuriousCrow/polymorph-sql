#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat widgets


CONFIG += plugin
CONFIG += c++11

TARGET = FirebirdPlugin
TEMPLATE = lib

include(../../sdk/sdk.pri)

SOURCES += \
    firebirddatabase.cpp \
    firebirdfolderitem.cpp \
    firebirdplugin.cpp \
    firebirdtable.cpp


HEADERS  += \
    firebirddatabase.h \
    firebirdfolderitem.h \
    firebirdplugin.h \
    firebirdtable.h


#FORMS    += \

DISTFILES += FirebirdPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

