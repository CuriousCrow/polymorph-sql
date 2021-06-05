#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T00:03:36
#
#-------------------------------------------------

QT       += core gui sql core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DemalexManager
TEMPLATE = app

RC_ICONS = icons/cc_16.ico

SOURCES += main.cpp\
#Core
  blobeditor.cpp \
  core/basepluginmanager.cpp \
  core/core.cpp \
  core/datastore.cpp \
  core/localeventnotifier.cpp \
  core/maphelplookupprovider.cpp \
  core/sqlhelplookupprovider.cpp \
  core/appsettings.cpp \
  databaseexportform.cpp \
  plugins/FIREBIRD/firebirddatabase.cpp \
  plugins/FIREBIRD/firebirdplugin.cpp \
  plugins/FIREBIRD/firebirdtable.cpp \
  plugins/MYSQL/mysqldatabase.cpp \
  plugins/MYSQL/mysqlplugin.cpp \
  plugins/MYSQL/mysqltable.cpp \
  plugins/POSTGRES/postgresplugin.cpp \
  plugins/POSTGRES/postgresviewitem.cpp \
  plugins/SQLITE/sqlitedatabase.cpp \
  plugins/SQLITE/sqliteplugin.cpp \
  plugins/SQLITE/sqlitetable.cpp \
  plugins/SQLITE/sqliteviewitem.cpp \
  sdk/objects/dbselectableitem.cpp \
  sdk/forms/queryparamsform.cpp \
  itemviewer.cpp \
  ltextcompleter.cpp \
  models/jointdbojbectmodel.cpp \
  models/ldbobjecttablemodel.cpp \
  models/queryparamtablemodel.cpp \
  sdk/dependencycontainer.cpp \
  models/unisqltablemodel.cpp \
  qknowledgebase.cpp \
#Forms
  sdk/forms/abstractdatabaseitemform.cpp \
  sdk/forms/tableeditform.cpp \
  sdk/forms/checkconstrainteditform.cpp \
  sdk/forms/foreignkeyform.cpp \
  sdk/forms/procedureeditform.cpp \
  sdk/forms/sequenceeditform.cpp \
  sdk/forms/triggereditform.cpp \
  sdk/forms/uniqueconstrainteditform.cpp \
  sdk/forms/vieweditdialog.cpp \
  mainwindow.cpp \
  sdk/forms/connectioneditdialog.cpp \
  queryhistoryform.cpp \
  settingsform.cpp \
  tablebrowserdelegate.cpp \
  tablebrowserwindow.cpp \
  queryeditorwindow.cpp \
  lqueryeditor.cpp \
#Utils
    qsqlqueryhelper.cpp \
    qsqlsyntaxhighlighter.cpp \
    utils/eventinterceptors.cpp \
    utils/qfileutils.cpp \
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
    sdk/objects/appurl.cpp \
    sdk/objects/dbobjectitem.cpp \
    sdk/objects/dbdatabaseitem.cpp \
    sdk/objects/dbtableitem.cpp \
    sdk/objects/dbsequenceitem.cpp \
    sdk/objects/dbtriggeritem.cpp \
    sdk/objects/dbprocedureitem.cpp \
    sdk/objects/dbviewitem.cpp \
    sdk/objects/foldertreeitem.cpp \
    sdk/objects/dbcheckconstraint.cpp \
    sdk/objects/dbconstraintitem.cpp \
    sdk/objects/dbforeignkey.cpp \
    sdk/objects/dbprimarykey.cpp \
    sdk/objects/dbuniqueconstraint.cpp \
#SQLite
#MySQL
#Postgres
    plugins/POSTGRES/postgrestriggeritem.cpp \
    plugins/POSTGRES/postgrescheckconstraint.cpp \
    plugins/POSTGRES/postgresdatabase.cpp \
    plugins/POSTGRES/postgresforeignkey.cpp \
    plugins/POSTGRES/postgresfunction.cpp \
    plugins/POSTGRES/postgresprimarykey.cpp \
    plugins/POSTGRES/postgressequence.cpp \
    plugins/POSTGRES/postgrestable.cpp \
    plugins/POSTGRES/postgresuniqueconstraint.cpp \
    plugins/POSTGRES/postgresfolderitem.cpp \
    utils/sqlfiltermanager.cpp \
    utils/sqlutils.cpp \
    utils/strutils.cpp
#Firebird

HEADERS  += \
#Core
  blobeditor.h \
  core/basepluginmanager.h \
  core/core.h \
  core/datastore.h \
  core/localeventnotifier.h \
  core/maphelplookupprovider.h \
  core/sqlhelplookupprovider.h \
  core/appsettings.h \
  databaseexportform.h \
  plugins/FIREBIRD/firebirddatabase.h \
  plugins/FIREBIRD/firebirdplugin.h \
  plugins/FIREBIRD/firebirdtable.h \
  plugins/MYSQL/mysqldatabase.h \
  plugins/MYSQL/mysqlplugin.h \
  plugins/MYSQL/mysqltable.h \
  plugins/POSTGRES/postgresplugin.h \
  plugins/POSTGRES/postgresviewitem.h \
  plugins/SQLITE/sqlitedatabase.h \
  plugins/SQLITE/sqliteplugin.h \
  plugins/SQLITE/sqlitetable.h \
  plugins/SQLITE/sqliteviewitem.h \
  sdk/objects/dbmsplugin.h \
  sdk/objects/dbselectableitem.h \
  sdk/forms/queryparamsform.h \
  sdk/abstractpluginmanager.h \
  sdk/dependencycontainer.h \
  itemviewer.h \
  ltextcompleter.h \
  models/jointdbojbectmodel.h \
  models/ldbobjecttablemodel.h \
  models/queryparamtablemodel.h \
  models/unisqltablemodel.h \
  qknowledgebase.h \
#Forms
  sdk/forms/abstractdatabaseitemform.h \
  sdk/forms/tableeditform.h \
  sdk/forms/checkconstrainteditform.h \
  sdk/forms/foreignkeyform.h \
  sdk/forms/procedureeditform.h \
  sdk/forms/sequenceeditform.h \
  sdk/forms/triggereditform.h \
  sdk/forms/uniqueconstrainteditform.h \
  sdk/forms/vieweditdialog.h \
  mainwindow.h \
  sdk/forms/connectioneditdialog.h \
  queryhistoryform.h \
  settingsform.h \
  tablebrowserdelegate.h \
  tablebrowserwindow.h \
  queryeditorwindow.h \
  lqueryeditor.h \
#Utils
    qsqlqueryhelper.h \
    qsqlsyntaxhighlighter.h \
    utils/eventinterceptors.h \
    utils/qfileutils.h \
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
    sdk/objects/appconst.h \
    sdk/objects/appurl.h \
    sdk/objects/dbobjectitem.h \
    sdk/objects/dbdatabaseitem.h \
    sdk/objects/dbtableitem.h \
    sdk/objects/dbsequenceitem.h \
    sdk/objects/dbtriggeritem.h \
    sdk/objects/dbprocedureitem.h \
    sdk/objects/dbviewitem.h \
    sdk/objects/foldertreeitem.h \
    sdk/objects/dbcheckconstraint.h \
    sdk/objects/dbconstraintitem.h \
    sdk/objects/dbforeignkey.h \
    sdk/objects/dbprimarykey.h \
    sdk/objects/dbuniqueconstraint.h \
#SQLite
#MySQL
#Postgres
    plugins/POSTGRES/postgrestriggeritem.h \
    plugins/POSTGRES/postgrescheckconstraint.h \
    plugins/POSTGRES/postgresdatabase.h \
    plugins/POSTGRES/postgresforeignkey.h \
    plugins/POSTGRES/postgresfunctionitem.h \
    plugins/POSTGRES/postgresprimarykey.h \
    plugins/POSTGRES/postgressequence.h \
    plugins/POSTGRES/postgrestable.h \
    plugins/POSTGRES/postgresuniqueconstraint.h \
    plugins/POSTGRES/postgresfolderitem.h \
    utils/sqlfiltermanager.h \
    utils/sqlutils.h \
    utils/strutils.h
#Firebird

FORMS    += mainwindow.ui \
    blobeditor.ui \
    databaseexportform.ui \
    sdk/forms/connectioneditdialog.ui \
    sdk/forms/checkconstrainteditform.ui \
    sdk/forms/foreignkeyform.ui \
    sdk/forms/procedureeditform.ui \
    sdk/forms/queryparamsform.ui \
    sdk/forms/sequenceeditform.ui \
    sdk/forms/triggereditform.ui \
    sdk/forms/uniqueconstrainteditform.ui \
    itemviewer.ui \
    queryhistoryform.ui \
    settingsform.ui \
    tablebrowserwindow.ui \
    queryeditorwindow.ui \
    sdk/forms/vieweditdialog.ui \
    sdk/forms/tableeditform.ui

RESOURCES += \
    icons.qrc
