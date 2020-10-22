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
#Core
  core/core.cpp \
  core/datastore.cpp \
  core/localeventnotifier.cpp \
  core/maphelplookupprovider.cpp \
  core/sqlhelplookupprovider.cpp \
  core/appsettings.cpp \
  dbms/FIREBIRD/firebirddatabase.cpp \
  dbms/FIREBIRD/firebirdplugin.cpp \
  dbms/FIREBIRD/firebirdtable.cpp \
  dbms/MYSQL/mysqldatabase.cpp \
  dbms/MYSQL/mysqlplugin.cpp \
  dbms/MYSQL/mysqltable.cpp \
  dbms/POSTGRES/postgresplugin.cpp \
  dbms/POSTGRES/postgresviewitem.cpp \
  dbms/SQLITE/sqlitedatabase.cpp \
  dbms/SQLITE/sqliteplugin.cpp \
  dbms/SQLITE/sqlitetable.cpp \
  dbms/SQLITE/sqliteviewitem.cpp \
  ltextcompleter.cpp \
  models/jointdbojbectmodel.cpp \
  models/ldbobjecttablemodel.cpp \
  models/unisqltablemodel.cpp \
  qknowledgebase.cpp \
#Forms
  forms/abstractdatabaseitemform.cpp \
  forms/tableeditform.cpp \
  forms/checkconstrainteditform.cpp \
  forms/foreignkeyform.cpp \
  forms/procedureeditform.cpp \
  forms/sequenceeditform.cpp \
  forms/triggereditform.cpp \
  forms/uniqueconstrainteditform.cpp \
  forms/vieweditdialog.cpp \
  mainwindow.cpp \
  forms/connectioneditdialog.cpp \
  tablebrowserdelegate.cpp \
  tablebrowserwindow.cpp \
  queryeditorwindow.cpp \
  lqueryeditor.cpp \
#Utils
  qsqlqueryhelper.cpp \
  qsqlsyntaxhighlighter.cpp \
  utils/qsimpletooltip.cpp \
#Models
    models/simplecachedtablemodel.cpp \
    models/comboboxitemdelegate.cpp \
    models/lcachedtablemodel.cpp \
    models/lsqltablemodel.cpp \
    qstructureitemmodel.cpp \
    tablerowmodel.cpp \
    models/variantmaptablemodel.cpp \
    ldbobjectmodel.cpp \
    qactiveconnectionmodel.cpp \
    lstandardtreemodel.cpp \
    ldatawidgetmapper.cpp \
    models/sqlcolumnmodel.cpp \
    comboboxhashdelegate.cpp \
#Base DB classes
    dbms/appurl.cpp \
    dbms/dbobjectitem.cpp \
    dbms/dbdatabaseitem.cpp \
    dbms/dbtableitem.cpp \
    dbms/dbsequenceitem.cpp \
    dbms/dbtriggeritem.cpp \
    dbms/dbprocedureitem.cpp \
    dbms/dbviewitem.cpp \
    dbms/foldertreeitem.cpp \
    dbms/dbcheckconstraint.cpp \
    dbms/dbconstraintitem.cpp \
    dbms/dbforeignkey.cpp \
    dbms/dbprimarykey.cpp \
    dbms/dbuniqueconstraint.cpp \
#SQLite
#MySQL
#Postgres
    dbms/POSTGRES/postgrestriggeritem.cpp \
    dbms/POSTGRES/postgrescheckconstraint.cpp \
    dbms/POSTGRES/postgresdatabase.cpp \
    dbms/POSTGRES/postgresforeignkey.cpp \
    dbms/POSTGRES/postgresfunction.cpp \
    dbms/POSTGRES/postgresprimarykey.cpp \
    dbms/POSTGRES/postgressequence.cpp \
    dbms/POSTGRES/postgrestable.cpp \
    dbms/POSTGRES/postgresuniqueconstraint.cpp \
    utils/sqlfiltermanager.cpp \
  utils/sqlutils.cpp
#Firebird

HEADERS  += \
#Core
  core/core.h \
  core/datastore.h \
  core/localeventnotifier.h \
  core/maphelplookupprovider.h \
  core/sqlhelplookupprovider.h \
  core/appsettings.h \
  dbms/FIREBIRD/firebirddatabase.h \
  dbms/FIREBIRD/firebirdplugin.h \
  dbms/FIREBIRD/firebirdtable.h \
  dbms/MYSQL/mysqldatabase.h \
  dbms/MYSQL/mysqlplugin.h \
  dbms/MYSQL/mysqltable.h \
  dbms/POSTGRES/postgresplugin.h \
  dbms/POSTGRES/postgresviewitem.h \
  dbms/SQLITE/sqlitedatabase.h \
  dbms/SQLITE/sqliteplugin.h \
  dbms/SQLITE/sqlitetable.h \
  dbms/SQLITE/sqliteviewitem.h \
  dbms/dbmsplugin.h \
  ltextcompleter.h \
  models/jointdbojbectmodel.h \
  models/ldbobjecttablemodel.h \
  models/unisqltablemodel.h \
  qknowledgebase.h \
#Forms
  forms/abstractdatabaseitemform.h \
  forms/tableeditform.h \
  forms/checkconstrainteditform.h \
  forms/foreignkeyform.h \
  forms/procedureeditform.h \
  forms/sequenceeditform.h \
  forms/triggereditform.h \
  forms/uniqueconstrainteditform.h \
  forms/vieweditdialog.h \
  mainwindow.h \
  forms/connectioneditdialog.h \
  tablebrowserdelegate.h \
  tablebrowserwindow.h \
  queryeditorwindow.h \
  lqueryeditor.h \
#Utils
  qsqlqueryhelper.h \
  qsqlsyntaxhighlighter.h \
  utils/qsimpletooltip.h \
#Models
    models/simplecachedtablemodel.h \
    models/comboboxitemdelegate.h \
    models/lcachedtablemodel.h \
    models/lsqltablemodel.h \
    qstructureitemmodel.h \
    tablerowmodel.h \
    models/variantmaptablemodel.h \
    ldbobjectmodel.h \
    qactiveconnectionmodel.h \
    lstandardtreemodel.h \
    ldatawidgetmapper.h \
    models/sqlcolumnmodel.h \
    comboboxhashdelegate.h \
#Base DB classes
    dbms/appconst.h \
    dbms/appurl.h \
    dbms/dbobjectitem.h \
    dbms/dbdatabaseitem.h \
    dbms/dbtableitem.h \
    dbms/dbsequenceitem.h \
    dbms/dbtriggeritem.h \
    dbms/dbprocedureitem.h \
    dbms/dbviewitem.h \
    dbms/foldertreeitem.h \
    dbms/dbcheckconstraint.h \
    dbms/dbconstraintitem.h \
    dbms/dbforeignkey.h \
    dbms/dbprimarykey.h \
    dbms/dbuniqueconstraint.h \
#SQLite
#MySQL
#Postgres
    dbms/POSTGRES/postgrestriggeritem.h \
    dbms/POSTGRES/postgrescheckconstraint.h \
    dbms/POSTGRES/postgresdatabase.h \
    dbms/POSTGRES/postgresforeignkey.h \
    dbms/POSTGRES/postgresfunctionitem.h \
    dbms/POSTGRES/postgresprimarykey.h \
    dbms/POSTGRES/postgressequence.h \
    dbms/POSTGRES/postgrestable.h \
    dbms/POSTGRES/postgresuniqueconstraint.h \
  utils/sqlfiltermanager.h \
  utils/sqlutils.h
#Firebird

FORMS    += mainwindow.ui \
    forms/connectioneditdialog.ui \
    forms/checkconstrainteditform.ui \
    forms/foreignkeyform.ui \
    forms/procedureeditform.ui \
    forms/sequenceeditform.ui \
    forms/triggereditform.ui \
    forms/uniqueconstrainteditform.ui \
    tablebrowserwindow.ui \
    queryeditorwindow.ui \
    forms/vieweditdialog.ui \
    forms/tableeditform.ui

RESOURCES += \
    icons.qrc
