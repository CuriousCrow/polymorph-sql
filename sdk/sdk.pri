INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

SOURCES += \
#Core
  sdk/core/core.cpp \
  sdk/core/datastore.cpp \
  sdk/core/localeventnotifier.cpp \
  sdk/core/maphelplookupprovider.cpp \
  sdk/core/sqlhelplookupprovider.cpp \
  sdk/core/appsettings.cpp \
  sdk/core/iocplugin.cpp \
  sdk/objects/dbselectableitem.cpp \
  sdk/forms/queryparamsform.cpp \
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
  sdk/forms/connectioneditdialog.cpp \
  sdk/objects/sdkplugin.cpp \
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
    sdk/utils/sqlfiltermanager.cpp \
    sdk/utils/sqlutils.cpp \
    sdk/utils/strutils.cpp
#Firebird

HEADERS  += \
#Core
  sdk/core/core.h \
  sdk/core/datastore.h \
  sdk/core/localeventnotifier.h \
  sdk/core/maphelplookupprovider.h \
  sdk/core/sqlhelplookupprovider.h \
  sdk/core/appsettings.h \
  sdk/core/iocplugin.h \
  sdk/objects/dbmsplugin.h \
  sdk/objects/dbselectableitem.h \
  sdk/forms/queryparamsform.h \
  sdk/abstractplugin.h \
  sdk/core/dependencycontainer.h \
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
  sdk/forms/connectioneditdialog.h \
  sdk/objects/sdkplugin.h \
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
    sdk/utils/sqlfiltermanager.h \
    sdk/utils/sqlutils.h \
    sdk/utils/strutils.h
#Firebird

FORMS    += \
    sdk/forms/connectioneditdialog.ui \
    sdk/forms/checkconstrainteditform.ui \
    sdk/forms/foreignkeyform.ui \
    sdk/forms/procedureeditform.ui \
    sdk/forms/queryparamsform.ui \
    sdk/forms/sequenceeditform.ui \
    sdk/forms/triggereditform.ui \
    sdk/forms/uniqueconstrainteditform.ui \
    sdk/forms/vieweditdialog.ui \
    sdk/forms/tableeditform.ui

