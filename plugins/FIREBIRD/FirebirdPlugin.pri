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
    $$PWD/firebirdtrigger.cpp \
    $$PWD/firebirduniqueconstraint.cpp \
    $$PWD/firebirdview.cpp \
    $$PWD/firebirdtriggerform.cpp \
    $$PWD/firebirdutils.cpp \
    $$PWD/firebirdprocedure.cpp \
    $$PWD/firebirdprocedureform.cpp


HEADERS  += \
    $$PWD/firebirdcheckconstraint.h \
    $$PWD/firebirddatabase.h \
    $$PWD/firebirdfolderitem.h \
    $$PWD/firebirdforeignkey.h \
    $$PWD/firebirdplugin.h \
    $$PWD/firebirdprimarykey.h \
    $$PWD/firebirdtable.h \
    $$PWD/firebirdsequence.h \
    $$PWD/firebirdtrigger.h \
    $$PWD/firebirduniqueconstraint.h \
    $$PWD/firebirdview.h \
    $$PWD/firebirdtriggerform.h \
    $$PWD/firebirdutils.h \
    $$PWD/firebirdprocedure.h \
    $$PWD/firebirdprocedureform.h


FORMS    += \
    $$PWD/firebirdtriggerform.ui \
    $$PWD/firebirdprocedureform.ui


TRANSLATIONS += \
    $$PWD/translations/firebirdplugin_ru.ts

