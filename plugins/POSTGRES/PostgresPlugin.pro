#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat widgets


CONFIG += plugin
CONFIG += c++11

TARGET = PostgresPlugin
TEMPLATE = lib

include(../../sdk/sdk.pri)

SOURCES += \
    postgrescheckconstraint.cpp \
    postgresdatabase.cpp \
    postgresfolderitem.cpp \
    postgresforeignkey.cpp \
    postgresfunctionitem.cpp \
    postgresplugin.cpp \
    postgresprimarykey.cpp \
    postgressequence.cpp \
    postgrestable.cpp \
    postgrestriggeritem.cpp \
    postgresuniqueconstraint.cpp \
    postgresviewitem.cpp


HEADERS  += \
    postgrescheckconstraint.h \
    postgresdatabase.h \
    postgresfolderitem.h \
    postgresforeignkey.h \
    postgresfunctionitem.h \
    postgresplugin.h \
    postgresprimarykey.h \
    postgressequence.h \
    postgrestable.h \
    postgrestriggeritem.h \
    postgresuniqueconstraint.h \
    postgresviewitem.h


#FORMS    += \

DISTFILES += PostgresPlugin.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

