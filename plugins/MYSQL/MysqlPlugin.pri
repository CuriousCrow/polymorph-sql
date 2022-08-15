INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/mysqldatabase.cpp \
    $$PWD/mysqlfolderitem.cpp \
    $$PWD/mysqlforeignkey.cpp \
    $$PWD/mysqlplugin.cpp \
    $$PWD/mysqlprimarykey.cpp \
    $$PWD/mysqltable.cpp \
    $$PWD/mysqlsequence.cpp \
    $$PWD/mysqluniqueconstraint.cpp \
    $$PWD/mysqlview.cpp \
    $$PWD/mysqlcheckconstraint.cpp


HEADERS  += \
    $$PWD/mysqldatabase.h \
    $$PWD/mysqlfolderitem.h \
    $$PWD/mysqlforeignkey.h \
    $$PWD/mysqlplugin.h \
    $$PWD/mysqlprimarykey.h \
    $$PWD/mysqltable.h \
    $$PWD/mysqlsequence.h \
    $$PWD/mysqluniqueconstraint.h \
    $$PWD/mysqlview.h \
    $$PWD/mysqlcheckconstraint.h


#FORMS    += \

TRANSLATIONS += \
    $$PWD/translations/mysqlplugin_ru.ts
