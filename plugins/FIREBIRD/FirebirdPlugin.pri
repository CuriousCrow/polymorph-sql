INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

SOURCES += \
  $$PWD/objects/firebirdcheckconstraint.cpp \
  $$PWD/objects/firebirddatabase.cpp \
  $$PWD/objects/firebirdfolderitem.cpp \
  $$PWD/objects/firebirdforeignkey.cpp \
  $$PWD/objects/firebirdprimarykey.cpp \
  $$PWD/objects/firebirdtable.cpp \
  $$PWD/objects/firebirdsequence.cpp \
  $$PWD/objects/firebirdtrigger.cpp \
  $$PWD/objects/firebirduniqueconstraint.cpp \
  $$PWD/objects/firebirdview.cpp \
  $$PWD/objects/firebirdprocedure.cpp \
  $$PWD/objects/firebirddomain.cpp \
  $$PWD/forms/firebirdtriggerform.cpp \
  $$PWD/forms/firebirdprocedureform.cpp \
  $$PWD/forms/firebirddomainform.cpp \
  $$PWD/firebirdplugin.cpp \
  $$PWD/firebirdtypeprovider.cpp \
  $$PWD/firebirdutils.cpp

HEADERS  += \
  $$PWD/objects/firebirddatabase.h \
  $$PWD/objects/firebirdfolderitem.h \
  $$PWD/objects/firebirdforeignkey.h \
  $$PWD/objects/firebirdprimarykey.h \
  $$PWD/objects/firebirdtable.h \
  $$PWD/objects/firebirdsequence.h \
  $$PWD/objects/firebirdtrigger.h \
  $$PWD/objects/firebirdprocedure.h \
  $$PWD/objects/firebirduniqueconstraint.h \
  $$PWD/objects/firebirdview.h \
  $$PWD/objects/firebirdcheckconstraint.h \
  $$PWD/objects/firebirddomain.h \
  $$PWD/forms/firebirdtriggerform.h \
  $$PWD/forms/firebirdprocedureform.h \
  $$PWD/forms/firebirddomainform.h \
  $$PWD/firebirdutils.h \
  $$PWD/firebirdconst.h \
  $$PWD/firebirdplugin.h \
  $$PWD/firebirdtypeprovider.h

FORMS    += \
  $$PWD/forms/firebirdtriggerform.ui \
  $$PWD/forms/firebirdprocedureform.ui \
  $$PWD/forms/firebirddomainform.ui

TRANSLATIONS += \
  $$PWD/translations/firebirdplugin_ru.ts

