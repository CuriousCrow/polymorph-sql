#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app

RC_ICONS = icons/cc_16.ico

SOURCES += main.cpp\
  core/localeventnotifier.cpp \
        mainwindow.cpp \
    connectioneditdialog.cpp \
    tablebrowserwindow.cpp \
    lsqltablemodel.cpp \
    qstructureitemmodel.cpp \
    dbms/qdbobjectitem.cpp \
    dbms/qdbdatabaseitem.cpp \
    dbms/qdbtableitem.cpp \
    dbms/qdbsequenceitem.cpp \
    dbms/qdbtriggeritem.cpp \
    dbms/qdbprocedureitem.cpp \
    dbms/qdbviewitem.cpp \
    dbms/qfoldertreeitem.cpp \
    queryeditorwindow.cpp \
    lstandardtreemodel.cpp \
    ldatawidgetmapper.cpp \
    qsqlqueryhelper.cpp \
    qsqlsyntaxhighlighter.cpp \
    qactiveconnectionmodel.cpp \
    ltextcompleter.cpp \
    vieweditdialog.cpp \
    qknowledgebase.cpp \
    dbms/FIREBIRD/qdbfirebirditem.cpp \
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
    dbms\SQLITE\qdbsqliteitem.cpp \
    dbms\SQLITE\qdbsqlitetableitem.cpp \
    models/sqlcolumnmodel.cpp \
    comboboxhashdelegate.cpp \
    dbms\MYSQL\qdbmysqltableitem.cpp \
    dbms\MYSQL\qdbmysqlitem.cpp \
    dbms/POSTGRES/qdbpostgresitem.cpp \
    dbms/POSTGRES/qdbpostgrestableitem.cpp \
    dbms/FIREBIRD/qdbfirebirdtableitem.cpp

HEADERS  += mainwindow.h \
    connectioneditdialog.h \
    core/localeventnotifier.h \
    tablebrowserwindow.h \
    lsqltablemodel.h \
    qstructureitemmodel.h \
    dbms/qdbobjectitem.h \
    dbms/qdbdatabaseitem.h \
    dbms/qdbtableitem.h \
    dbms/qdbsequenceitem.h \
    dbms/qdbtriggeritem.h \
    dbms/qdbprocedureitem.h \
    dbms/qdbviewitem.h \
    dbms/qfoldertreeitem.h \
    queryeditorwindow.h \
    lstandardtreemodel.h \
    ldatawidgetmapper.h \
    qsqlqueryhelper.h \
    qsqlsyntaxhighlighter.h \
    qactiveconnectionmodel.h \
    ltextcompleter.h \
    vieweditdialog.h \
    qknowledgebase.h \
    dbms/FIREBIRD/qdbfirebirditem.h \
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
    dbms\SQLITE\qdbsqliteitem.h \
    dbms\SQLITE\qdbsqlitetableitem.h \
    models/sqlcolumnmodel.h \
    comboboxhashdelegate.h \
    dbms\MYSQL\qdbmysqltableitem.h \
    dbms\MYSQL\qdbmysqlitem.h \
    dbms/POSTGRES/qdbpostgresitem.h \
    dbms/POSTGRES/qdbpostgrestableitem.h \
    dbms/FIREBIRD/qdbfirebirdtableitem.h

FORMS    += mainwindow.ui \
    connectioneditdialog.ui \
    tablebrowserwindow.ui \
    queryeditorwindow.ui \
    vieweditdialog.ui \
    forms/tableeditform.ui

RESOURCES += \
    icons.qrc
