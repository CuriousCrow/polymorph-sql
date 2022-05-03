INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/firebirddatabase.cpp \
    $$PWD/firebirdfolderitem.cpp \
    $$PWD/firebirdplugin.cpp \
    $$PWD/firebirdtable.cpp \
    $$PWD/firebirdsequence.cpp


HEADERS  += \
    $$PWD/firebirddatabase.h \
    $$PWD/firebirdfolderitem.h \
    $$PWD/firebirdplugin.h \
    $$PWD/firebirdtable.h \
    $$PWD/firebirdsequence.h


#FORMS    += \


TRANSLATIONS += \
    $$PWD/translations/firebirdplugin_ru.ts

