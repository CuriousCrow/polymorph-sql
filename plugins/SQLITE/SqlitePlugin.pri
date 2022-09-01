INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets


SOURCES += \
  $$PWD/objects/sqlitedatabase.cpp \
  $$PWD/objects/sqlitefolderitem.cpp \
  $$PWD/objects/sqlitetable.cpp \
  $$PWD/objects/sqliteviewitem.cpp \
  $$PWD/sqliteplugin.cpp

HEADERS  += \
  $$PWD/objects/sqlitedatabase.h \
  $$PWD/objects/sqlitefolderitem.h \
  $$PWD/objects/sqlitetable.h \
  $$PWD/objects/sqliteviewitem.h \
  $$PWD/sqliteplugin.h

#FORMS    += \

TRANSLATIONS += \
    $$PWD/translations/sqliteplugin_ru.ts
