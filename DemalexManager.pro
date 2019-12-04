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
  core/datastore.cpp \
  core/localeventnotifier.cpp \
  dbms/POSTGRES/postgrestriggeritem.cpp \
  dbms/POSTGRES/dbpostgreqfunctionitem.cpp \
  dbms/POSTGRES/dbpostgresequence.cpp \
  dbms/appurl.cpp \
  dbms/dbcheckconstraint.cpp \
  dbms/dbconstraintitem.cpp \
  dbms/dbforeignkey.cpp \
  dbms/dbuniqueconstraint.cpp \
  forms/addforeignkeyform.cpp \
  forms/checkconstrainteditform.cpp \
  forms/procedureeditform.cpp \
  forms/sequenceeditform.cpp \
  forms/triggereditform.cpp \
  forms/uniqueconstrainteditform.cpp \
        mainwindow.cpp \
    connectioneditdialog.cpp \
  models/variantmaptablemodel.cpp \
    tablebrowserwindow.cpp \
    lsqltablemodel.cpp \
    qstructureitemmodel.cpp \
    dbms/dbobjectitem.cpp \
    dbms/dbdatabaseitem.cpp \
    dbms/dbtableitem.cpp \
    dbms/dbsequenceitem.cpp \
    dbms/dbtriggeritem.cpp \
    dbms/dbprocedureitem.cpp \
    dbms/dbviewitem.cpp \
    dbms/foldertreeitem.cpp \
    queryeditorwindow.cpp \
    lstandardtreemodel.cpp \
    ldatawidgetmapper.cpp \
    qsqlqueryhelper.cpp \
    qsqlsyntaxhighlighter.cpp \
    qactiveconnectionmodel.cpp \
    ltextcompleter.cpp \
    forms/vieweditdialog.cpp \
    qknowledgebase.cpp \
    dbms/FIREBIRD/dbfirebirditem.cpp \
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
    dbms\SQLITE\dbsqliteitem.cpp \
    dbms\SQLITE\dbsqlitetableitem.cpp \
    models/sqlcolumnmodel.cpp \
    comboboxhashdelegate.cpp \
    dbms\MYSQL\dbmysqltableitem.cpp \
    dbms\MYSQL\dbmysqlitem.cpp \
    dbms/POSTGRES/dbpostgresitem.cpp \
    dbms/POSTGRES/dbpostgrestableitem.cpp \
    dbms/FIREBIRD/dbfirebirdtableitem.cpp

HEADERS  += mainwindow.h \
    connectioneditdialog.h \
    core/datastore.h \
    core/localeventnotifier.h \
    dbms/POSTGRES/postgrestriggeritem.h \
    dbms/POSTGRES/dbpostgreqfunctionitem.h \
    dbms/POSTGRES/dbpostgresequence.h \
    dbms/appconst.h \
    dbms/appurl.h \
    dbms/dbcheckconstraint.h \
    dbms/dbconstraintitem.h \
    dbms/dbforeignkey.h \
    dbms/dbuniqueconstraint.h \
    forms/addforeignkeyform.h \
    forms/checkconstrainteditform.h \
    forms/procedureeditform.h \
    forms/sequenceeditform.h \
    forms/triggereditform.h \
    forms/uniqueconstrainteditform.h \
    models/variantmaptablemodel.h \
    tablebrowserwindow.h \
    lsqltablemodel.h \
    qstructureitemmodel.h \
    dbms/dbobjectitem.h \
    dbms/dbdatabaseitem.h \
    dbms/dbtableitem.h \
    dbms/dbsequenceitem.h \
    dbms/dbtriggeritem.h \
    dbms/dbprocedureitem.h \
    dbms/dbviewitem.h \
    dbms/foldertreeitem.h \
    queryeditorwindow.h \
    lstandardtreemodel.h \
    ldatawidgetmapper.h \
    qsqlqueryhelper.h \
    qsqlsyntaxhighlighter.h \
    qactiveconnectionmodel.h \
    ltextcompleter.h \
    forms/vieweditdialog.h \
    qknowledgebase.h \
    dbms/FIREBIRD/dbfirebirditem.h \
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
    dbms\SQLITE\dbsqliteitem.h \
    dbms\SQLITE\dbsqlitetableitem.h \
    models/sqlcolumnmodel.h \
    comboboxhashdelegate.h \
    dbms\MYSQL\dbmysqltableitem.h \
    dbms\MYSQL\dbmysqlitem.h \
    dbms/POSTGRES/dbpostgresitem.h \
    dbms/POSTGRES/dbpostgrestableitem.h \
    dbms/FIREBIRD/dbfirebirdtableitem.h

FORMS    += mainwindow.ui \
    connectioneditdialog.ui \
    forms/addforeignkeyform.ui \
    forms/checkconstrainteditform.ui \
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
