INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
    $$PWD/objects/postgrescheckconstraint.cpp \
    $$PWD/objects/postgresdatabase.cpp \
    $$PWD/objects/postgresfolderitem.cpp \
    $$PWD/objects/postgresforeignkey.cpp \
    $$PWD/objects/postgresfunction.cpp \
    $$PWD/objects/postgresprimarykey.cpp \
    $$PWD/objects/postgressequence.cpp \
    $$PWD/objects/postgrestable.cpp \
    $$PWD/objects/postgrestrigger.cpp \
    $$PWD/objects/postgresuniqueconstraint.cpp \
    $$PWD/objects/postgresview.cpp \
    $$PWD/postgresplugin.cpp


HEADERS  += \
    $$PWD/objects/postgrescheckconstraint.h \
    $$PWD/objects/postgresdatabase.h \
    $$PWD/objects/postgresfolderitem.h \
    $$PWD/objects/postgresforeignkey.h \
    $$PWD/objects/postgresfunction.h \
    $$PWD/objects/postgresprimarykey.h \
    $$PWD/objects/postgressequence.h \
    $$PWD/objects/postgrestable.h \
    $$PWD/objects/postgrestrigger.h \
    $$PWD/objects/postgresuniqueconstraint.h \
    $$PWD/objects/postgresview.h \
    $$PWD/postgresconst.h \
    $$PWD/postgresplugin.h


#FORMS    += \


TRANSLATIONS += \
    $$PWD/translations/postgresplugin_ru.ts
