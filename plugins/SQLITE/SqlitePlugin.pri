INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets


SOURCES += \
    $$PWD/sqlitedatabase.cpp \
    $$PWD/sqlitefolderitem.cpp \
    $$PWD/sqliteplugin.cpp \
    $$PWD/sqlitetable.cpp \
    $$PWD/sqliteviewitem.cpp

HEADERS  += \
    $$PWD/sqlitedatabase.h \
    $$PWD/sqlitefolderitem.h \
    $$PWD/sqliteplugin.h \
    $$PWD/sqlitetable.h \
    $$PWD/sqliteviewitem.h

#FORMS    += \

TRANSLATIONS += \
    $$PWD/translations/sqliteplugin_ru.ts
