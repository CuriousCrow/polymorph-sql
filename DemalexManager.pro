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
  core/datastore.cpp \
  core/localeventnotifier.cpp \
    core/maphelplookupprovider.cpp \
    core/sqlhelplookupprovider.cpp \
    core/appsettings.cpp \
    ltextcompleter.cpp \
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
  connectioneditdialog.cpp \
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
    lsqltablemodel.cpp \
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
    dbms\SQLITE\dbsqliteitem.cpp \
    dbms\SQLITE\dbsqlitetableitem.cpp \
#MySQL
    dbms\MYSQL\dbmysqltableitem.cpp \
    dbms\MYSQL\dbmysqlitem.cpp \
#Postgres
    dbms/POSTGRES/postgrestriggeritem.cpp \
    dbms/POSTGRES/dbpostgreqfunctionitem.cpp \
    dbms/POSTGRES/dbpostgresequence.cpp \
    dbms/POSTGRES/dbpostgresitem.cpp \
    dbms/POSTGRES/dbpostgrestableitem.cpp \
#Firebird
    dbms/FIREBIRD/dbfirebirditem.cpp \
    dbms/FIREBIRD/dbfirebirdtableitem.cpp

HEADERS  += \
#Core
    core/datastore.h \
    core/localeventnotifier.h \
    core/maphelplookupprovider.h \
    core/sqlhelplookupprovider.h \
    core/appsettings.h \
    ltextcompleter.h \
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
  connectioneditdialog.h \
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
    lsqltablemodel.h \
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
    dbms\SQLITE\dbsqliteitem.h \
    dbms\SQLITE\dbsqlitetableitem.h \
#MySQL
    dbms\MYSQL\dbmysqltableitem.h \
    dbms\MYSQL\dbmysqlitem.h \
#Postgres
    dbms/POSTGRES/postgrestriggeritem.h \
    dbms/POSTGRES/dbpostgreqfunctionitem.h \
    dbms/POSTGRES/dbpostgresequence.h \
    dbms/POSTGRES/dbpostgresitem.h \
    dbms/POSTGRES/dbpostgrestableitem.h \
#Firebird
    dbms/FIREBIRD/dbfirebirditem.h \
    dbms/FIREBIRD/dbfirebirdtableitem.h

FORMS    += mainwindow.ui \
    connectioneditdialog.ui \
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
