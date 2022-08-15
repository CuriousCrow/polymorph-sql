INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/firebirdcheckconstraint.cpp \
    $$PWD/firebirddatabase.cpp \
    $$PWD/firebirdfolderitem.cpp \
    $$PWD/firebirdforeignkey.cpp \
    $$PWD/firebirdplugin.cpp \
    $$PWD/firebirdprimarykey.cpp \
    $$PWD/firebirdtable.cpp \
    $$PWD/firebirdsequence.cpp \
    $$PWD/firebirduniqueconstraint.cpp \
    $$PWD/firebirdview.cpp


HEADERS  += \
    $$PWD/firebirdcheckconstraint.h \
    $$PWD/firebirddatabase.h \
    $$PWD/firebirdfolderitem.h \
    $$PWD/firebirdforeignkey.h \
    $$PWD/firebirdplugin.h \
    $$PWD/firebirdprimarykey.h \
    $$PWD/firebirdtable.h \
    $$PWD/firebirdsequence.h \
    $$PWD/firebirduniqueconstraint.h \
    $$PWD/firebirdview.h


#FORMS    += \


TRANSLATIONS += \
    $$PWD/translations/firebirdplugin_ru.ts

