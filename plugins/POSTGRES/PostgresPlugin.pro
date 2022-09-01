#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql widgets


CONFIG += plugin
CONFIG += c++11

TARGET = PostgresPlugin
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
  objects/postgrescheckconstraint.cpp \
  objects/postgresdatabase.cpp \
  objects/postgresfolderitem.cpp \
  objects/postgresforeignkey.cpp \
  objects/postgresfunctionitem.cpp \
  objects/postgresprimarykey.cpp \
  objects/postgressequence.cpp \
  objects/postgrestable.cpp \
  objects/postgrestriggeritem.cpp \
  objects/postgresuniqueconstraint.cpp \
  objects/postgresviewitem.cpp \
  postgresplugin.cpp


HEADERS  += \
  objects/postgrescheckconstraint.h \
  objects/postgresdatabase.h \
  objects/postgresfolderitem.h \
  objects/postgresforeignkey.h \
  objects/postgresfunctionitem.h \
  objects/postgresprimarykey.h \
  objects/postgressequence.h \
  objects/postgrestable.h \
  objects/postgrestriggeritem.h \
  objects/postgresuniqueconstraint.h \
  objects/postgresviewitem.h \
  postgresplugin.h


#FORMS    += \

DISTFILES += PostgresPlugin.json

TRANSLATIONS += \
    translations/postgresplugin_ru.ts

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

