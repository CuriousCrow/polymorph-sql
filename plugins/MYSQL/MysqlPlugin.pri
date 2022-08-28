INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/mysqldatabase.cpp \
    $$PWD/mysqlfolderitem.cpp \
    $$PWD/mysqlforeignkey.cpp \
    $$PWD/mysqlplugin.cpp \
    $$PWD/mysqlprimarykey.cpp \
    $$PWD/mysqlprocedure.cpp \
    $$PWD/mysqltable.cpp \
    $$PWD/mysqlsequence.cpp \
    $$PWD/mysqltrigger.cpp \
    $$PWD/mysqltypeprovider.cpp \
    $$PWD/mysqluniqueconstraint.cpp \
    $$PWD/mysqlview.cpp \
    $$PWD/mysqlcheckconstraint.cpp \
    $$PWD/mysqlprocedureeditform.cpp \
    $$PWD/mysqltriggerform.cpp


HEADERS  += \
    $$PWD/mysqldatabase.h \
    $$PWD/mysqlfolderitem.h \
    $$PWD/mysqlforeignkey.h \
    $$PWD/mysqlplugin.h \
    $$PWD/mysqlprimarykey.h \
    $$PWD/mysqlprocedure.h \
    $$PWD/mysqltable.h \
    $$PWD/mysqlsequence.h \
    $$PWD/mysqltrigger.h \
    $$PWD/mysqltypeprovider.h \
    $$PWD/mysqluniqueconstraint.h \
    $$PWD/mysqlview.h \
    $$PWD/mysqlcheckconstraint.h \
    $$PWD/mysqlprocedureeditform.h \
    $$PWD/mysqltriggerform.h


FORMS    += \
    $$PWD/mysqlprocedureeditform.ui \
    $$PWD/mysqltriggerform.ui

TRANSLATIONS += \
    $$PWD/translations/mysqlplugin_ru.ts
