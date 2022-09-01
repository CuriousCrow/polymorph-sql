INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
  $$PWD/objects/postgrescheckconstraint.cpp \
  $$PWD/objects/postgresdatabase.cpp \
  $$PWD/objects/postgresfolderitem.cpp \
  $$PWD/objects/postgresforeignkey.cpp \
  $$PWD/objects/postgresfunctionitem.cpp \
  $$PWD/objects/postgresprimarykey.cpp \
  $$PWD/objects/postgressequence.cpp \
  $$PWD/objects/postgrestable.cpp \
  $$PWD/objects/postgrestriggeritem.cpp \
  $$PWD/objects/postgresuniqueconstraint.cpp \
  $$PWD/objects/postgresviewitem.cpp \
  $$PWD/postgresplugin.cpp


HEADERS  += \
  $$PWD/objects/postgrescheckconstraint.h \
  $$PWD/objects/postgresdatabase.h \
  $$PWD/objects/postgresfolderitem.h \
  $$PWD/objects/postgresforeignkey.h \
  $$PWD/objects/postgresfunctionitem.h \
  $$PWD/objects/postgresprimarykey.h \
  $$PWD/objects/postgressequence.h \
  $$PWD/objects/postgrestable.h \
  $$PWD/objects/postgrestriggeritem.h \
  $$PWD/objects/postgresuniqueconstraint.h \
  $$PWD/objects/postgresviewitem.h \
  $$PWD/postgresplugin.h


#FORMS    += \


TRANSLATIONS += \
  $$PWD/translations/postgresplugin_ru.ts
