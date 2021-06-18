INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/mysqldatabase.cpp \
    $$PWD/mysqlfolderitem.cpp \
    $$PWD/mysqlplugin.cpp \
    $$PWD/mysqltable.cpp


HEADERS  += \
    $$PWD/mysqldatabase.h \
    $$PWD/mysqlfolderitem.h \
    $$PWD/mysqlplugin.h \
    $$PWD/mysqltable.h


#FORMS    += \


