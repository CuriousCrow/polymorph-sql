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
  widgets/blobeditor.cpp \
  sdk/core/core.cpp \
  sdk/core/datastore.cpp \
  sdk/core/localeventnotifier.cpp \
  sdk/core/maphelplookupprovider.cpp \
  sdk/core/sqlhelplookupprovider.cpp \
  sdk/core/appsettings.cpp \
  forms/databaseexportform.cpp \
  plugins/FIREBIRD/firebirddatabase.cpp \
  plugins/FIREBIRD/firebirdfolderitem.cpp \
  plugins/FIREBIRD/firebirdplugin.cpp \
  plugins/FIREBIRD/firebirdtable.cpp \
  plugins/MYSQL/mysqldatabase.cpp \
  plugins/MYSQL/mysqlfolderitem.cpp \
  plugins/MYSQL/mysqlplugin.cpp \
  plugins/MYSQL/mysqltable.cpp \
  plugins/POSTGRES/postgresfunctionitem.cpp \
  plugins/POSTGRES/postgresplugin.cpp \
  plugins/POSTGRES/postgresviewitem.cpp \
  plugins/SQLITE/sqlitedatabase.cpp \
  plugins/SQLITE/sqlitefolderitem.cpp \
  plugins/SQLITE/sqliteplugin.cpp \
  plugins/SQLITE/sqlitetable.cpp \
  plugins/SQLITE/sqliteviewitem.cpp \
  sdk/core/iocplugin.cpp \
  sdk/objects/dbselectableitem.cpp \
  sdk/forms/queryparamsform.cpp \
  widgets/itemviewer.cpp \
  sdk/tools/ltextcompleter.cpp \
  sdk/models/jointdbojbectmodel.cpp \
  sdk/models/ldbobjecttablemodel.cpp \
  sdk/models/queryparamtablemodel.cpp \
  sdk/core/dependencycontainer.cpp \
  sdk/models/unisqltablemodel.cpp \
  sdk/core/qknowledgebase.cpp \
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
  forms/mainwindow.cpp \
  sdk/forms/connectioneditdialog.cpp \
  forms/queryhistoryform.cpp \
  sdk/objects/sdkplugin.cpp \
  forms/settingsform.cpp \
  widgets/tablebrowserdelegate.cpp \
  forms/tablebrowserwindow.cpp \
  forms/queryeditorwindow.cpp \
  widgets/lqueryeditor.cpp \
#Utils
    sdk/utils/qsqlqueryhelper.cpp \
    sdk/tools/qsqlsyntaxhighlighter.cpp \
    sdk/utils/eventinterceptors.cpp \
    sdk/utils/qfileutils.cpp \
    sdk/utils/qsimpletooltip.cpp \
#Models
    sdk/models/simplecachedtablemodel.cpp \
    sdk/models/comboboxitemdelegate.cpp \
    sdk/models/lcachedtablemodel.cpp \
    sdk/models/lsqltablemodel.cpp \
    sdk/models/qstructureitemmodel.cpp \
    sdk/models/tablerowmodel.cpp \
    sdk/models/variantmaptablemodel.cpp \
    sdk/models/ldbobjectmodel.cpp \
    sdk/models/qactiveconnectionmodel.cpp \
    sdk/models/lstandardtreemodel.cpp \
    sdk/tools/ldatawidgetmapper.cpp \
    sdk/models/sqlcolumnmodel.cpp \
    sdk/models/comboboxhashdelegate.cpp \
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
    plugins/POSTGRES/postgresprimarykey.cpp \
    plugins/POSTGRES/postgressequence.cpp \
    plugins/POSTGRES/postgrestable.cpp \
    plugins/POSTGRES/postgresuniqueconstraint.cpp \
    plugins/POSTGRES/postgresfolderitem.cpp \
    sdk/utils/sqlfiltermanager.cpp \
    sdk/utils/sqlutils.cpp \
    sdk/utils/strutils.cpp
#Firebird

HEADERS  += \
#Core
  widgets/blobeditor.h \
  sdk/core/core.h \
  sdk/core/datastore.h \
  sdk/core/localeventnotifier.h \
  sdk/core/maphelplookupprovider.h \
  sdk/core/sqlhelplookupprovider.h \
  sdk/core/appsettings.h \
  forms/databaseexportform.h \
  plugins/FIREBIRD/firebirddatabase.h \
  plugins/FIREBIRD/firebirdfolderitem.h \
  plugins/FIREBIRD/firebirdplugin.h \
  plugins/FIREBIRD/firebirdtable.h \
  plugins/MYSQL/mysqldatabase.h \
  plugins/MYSQL/mysqlfolderitem.h \
  plugins/MYSQL/mysqlplugin.h \
  plugins/MYSQL/mysqltable.h \
  plugins/POSTGRES/postgresplugin.h \
  plugins/POSTGRES/postgresviewitem.h \
  plugins/SQLITE/sqlitedatabase.h \
  plugins/SQLITE/sqlitefolderitem.h \
  plugins/SQLITE/sqliteplugin.h \
  plugins/SQLITE/sqlitetable.h \
  plugins/SQLITE/sqliteviewitem.h \
  sdk/core/iocplugin.h \
  sdk/objects/dbmsplugin.h \
  sdk/objects/dbselectableitem.h \
  sdk/forms/queryparamsform.h \
  sdk/abstractplugin.h \
  sdk/core/dependencycontainer.h \
  widgets/itemviewer.h \
  sdk/tools/ltextcompleter.h \
  sdk/models/jointdbojbectmodel.h \
  sdk/models/ldbobjecttablemodel.h \
  sdk/models/queryparamtablemodel.h \
  sdk/models/unisqltablemodel.h \
  sdk/core/qknowledgebase.h \
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
  forms/mainwindow.h \
  sdk/forms/connectioneditdialog.h \
  forms/queryhistoryform.h \
  sdk/objects/sdkplugin.h \
  forms/settingsform.h \
  widgets/tablebrowserdelegate.h \
  forms/tablebrowserwindow.h \
  forms/queryeditorwindow.h \
  widgets/lqueryeditor.h \
#Utils
    sdk/utils/qsqlqueryhelper.h \
    sdk/tools/qsqlsyntaxhighlighter.h \
    sdk/utils/eventinterceptors.h \
    sdk/utils/qfileutils.h \
    sdk/utils/qsimpletooltip.h \
#Models
    sdk/models/simplecachedtablemodel.h \
    sdk/models/comboboxitemdelegate.h \
    sdk/models/lcachedtablemodel.h \
    sdk/models/lsqltablemodel.h \
    sdk/models/qstructureitemmodel.h \
    sdk/models/tablerowmodel.h \
    sdk/models/variantmaptablemodel.h \
    sdk/models/ldbobjectmodel.h \
    sdk/models/qactiveconnectionmodel.h \
    sdk/models/lstandardtreemodel.h \
    sdk/tools/ldatawidgetmapper.h \
    sdk/models/sqlcolumnmodel.h \
    sdk/models/comboboxhashdelegate.h \
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
    sdk/utils/sqlfiltermanager.h \
    sdk/utils/sqlutils.h \
    sdk/utils/strutils.h
#Firebird

FORMS    += forms/mainwindow.ui \
    widgets/blobeditor.ui \
    forms/databaseexportform.ui \
    sdk/forms/connectioneditdialog.ui \
    sdk/forms/checkconstrainteditform.ui \
    sdk/forms/foreignkeyform.ui \
    sdk/forms/procedureeditform.ui \
    sdk/forms/queryparamsform.ui \
    sdk/forms/sequenceeditform.ui \
    sdk/forms/triggereditform.ui \
    sdk/forms/uniqueconstrainteditform.ui \
    widgets/itemviewer.ui \
    forms/queryhistoryform.ui \
    forms/settingsform.ui \
    forms/tablebrowserwindow.ui \
    forms/queryeditorwindow.ui \
    sdk/forms/vieweditdialog.ui \
    sdk/forms/tableeditform.ui

RESOURCES += \
    icons.qrc
