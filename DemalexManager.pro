#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectioneditdialog.cpp \
    tablebrowserwindow.cpp \
    lsqltablemodel.cpp \
    qstructureitemmodel.cpp \
    qdbobjectitem.cpp \
    qdbdatabaseitem.cpp \
    qdbtableitem.cpp \
    queryeditorwindow.cpp \
    lstandardtreemodel.cpp \
    qfoldertreeitem.cpp \
    ldatawidgetmapper.cpp \
    qsqlqueryhelper.cpp \
    qsqlsyntaxhighlighter.cpp \
    qactiveconnectionmodel.cpp \
    ltextcompleter.cpp \
    qdbsequenceitem.cpp \
    qdbtriggeritem.cpp \
    qdbprocedureitem.cpp \
    qdbviewitem.cpp \
    vieweditdialog.cpp \
    qknowledgebase.cpp \
    qdbfirebirditem.cpp \
    ldbobjectmodel.cpp \
    lqueryeditor.cpp \
    core/maphelplookupprovider.cpp \
    utils/qsimpletooltip.cpp \
    core/sqlhelplookupprovider.cpp \
    forms/abstractdatabaseitemform.cpp \
    forms/tableeditform.cpp \
    tablerowmodel.cpp \
    models/simplecachedtablemodel.cpp \
    models/comboboxitemdelegate.cpp \
    models/lcachedtablemodel.cpp \
    core/appsettings.cpp \
    qdbsqliteitem.cpp \
    qdbsqlitetableitem.cpp \
    models/sqlcolumnmodel.cpp \
    comboboxhashdelegate.cpp

HEADERS  += mainwindow.h \
    connectioneditdialog.h \
    tablebrowserwindow.h \
    lsqltablemodel.h \
    qstructureitemmodel.h \
    qdbobjectitem.h \
    qdbdatabaseitem.h \
    qdbtableitem.h \
    queryeditorwindow.h \
    lstandardtreemodel.h \
    qfoldertreeitem.h \
    ldatawidgetmapper.h \
    qsqlqueryhelper.h \
    qsqlsyntaxhighlighter.h \
    qactiveconnectionmodel.h \
    ltextcompleter.h \
    qdbsequenceitem.h \
    qdbtriggeritem.h \
    qdbprocedureitem.h \
    qdbviewitem.h \
    vieweditdialog.h \
    qknowledgebase.h \
    qdbfirebirditem.h \
    ldbobjectmodel.h \
    lqueryeditor.h \
    core/maphelplookupprovider.h \
    utils/qsimpletooltip.h \
    core/sqlhelplookupprovider.h \
    forms/abstractdatabaseitemform.h \
    forms/tableeditform.h \
    tablerowmodel.h \
    models/simplecachedtablemodel.h \
    models/comboboxitemdelegate.h \
    models/lcachedtablemodel.h \
    core/appsettings.h \
    qdbsqliteitem.h \
    qdbsqlitetableitem.h \
    models/sqlcolumnmodel.h \
    comboboxhashdelegate.h

FORMS    += mainwindow.ui \
    connectioneditdialog.ui \
    tablebrowserwindow.ui \
    queryeditorwindow.ui \
    vieweditdialog.ui \
    forms/tableeditform.ui

RESOURCES += \
    icons.qrc
