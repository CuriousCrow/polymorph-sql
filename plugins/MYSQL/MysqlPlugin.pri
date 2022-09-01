INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
  $$PWD/objects/mysqlprimarykey.cpp \
  $$PWD/objects/mysqlprocedure.cpp \
  $$PWD/objects/mysqltable.cpp \
  $$PWD/objects/mysqlsequence.cpp \
  $$PWD/objects/mysqltrigger.cpp \
  $$PWD/objects/mysqluniqueconstraint.cpp \
  $$PWD/objects/mysqlview.cpp \
  $$PWD/objects/mysqlcheckconstraint.cpp \
  $$PWD/objects/mysqldatabase.cpp \
  $$PWD/objects/mysqlfolderitem.cpp \
  $$PWD/objects/mysqlforeignkey.cpp \
  $$PWD/mysqlplugin.cpp \
  $$PWD/forms/mysqlprocedureeditform.cpp \
  $$PWD/forms/mysqltriggerform.cpp


HEADERS  += \
  $$PWD/objects/mysqldatabase.h \
  $$PWD/objects/mysqlfolderitem.h \
  $$PWD/objects/mysqlforeignkey.h \
  $$PWD/objects/mysqlprimarykey.h \
  $$PWD/objects/mysqlprocedure.h \
  $$PWD/objects/mysqltable.h \
  $$PWD/objects/mysqlsequence.h \
  $$PWD/objects/mysqltrigger.h \
  $$PWD/objects/mysqluniqueconstraint.h \
  $$PWD/objects/mysqlview.h \
  $$PWD/objects/mysqlcheckconstraint.h \
  $$PWD/mysqlplugin.h \
  $$PWD/forms/mysqlprocedureeditform.h \
  $$PWD/forms/mysqltriggerform.h


FORMS    += \
  $$PWD/forms/mysqlprocedureeditform.ui \
  $$PWD/forms/mysqltriggerform.ui

TRANSLATIONS += \
  $$PWD/translations/mysqlplugin_ru.ts
