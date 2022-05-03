INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/postgrescheckconstraint.cpp \
    $$PWD/postgresdatabase.cpp \
    $$PWD/postgresfolderitem.cpp \
    $$PWD/postgresforeignkey.cpp \
    $$PWD/postgresfunctionitem.cpp \
    $$PWD/postgresplugin.cpp \
    $$PWD/postgresprimarykey.cpp \
    $$PWD/postgressequence.cpp \
    $$PWD/postgrestable.cpp \
    $$PWD/postgrestriggeritem.cpp \
    $$PWD/postgresuniqueconstraint.cpp \
    $$PWD/postgresviewitem.cpp


HEADERS  += \
    $$PWD/postgrescheckconstraint.h \
    $$PWD/postgresdatabase.h \
    $$PWD/postgresfolderitem.h \
    $$PWD/postgresforeignkey.h \
    $$PWD/postgresfunctionitem.h \
    $$PWD/postgresplugin.h \
    $$PWD/postgresprimarykey.h \
    $$PWD/postgressequence.h \
    $$PWD/postgrestable.h \
    $$PWD/postgrestriggeritem.h \
    $$PWD/postgresuniqueconstraint.h \
    $$PWD/postgresviewitem.h


#FORMS    += \


TRANSLATIONS += \
    $$PWD/translations/postgresplugin_ru.ts
