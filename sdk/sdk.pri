INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

SOURCES += \
#Core
    $$PWD/core/core.cpp \
    $$PWD/core/datastore.cpp \
    $$PWD/core/localeventnotifier.cpp \
    $$PWD/core/maphelplookupprovider.cpp \
    $$PWD/core/sqlhelplookupprovider.cpp \
    $$PWD/core/appsettings.cpp \
    $$PWD/core/iocplugin.cpp \
    $$PWD/objects/dbselectableitem.cpp \
    $$PWD/forms/queryparamsform.cpp \
    $$PWD/tools/ltextcompleter.cpp \
    $$PWD/models/jointdbojbectmodel.cpp \
    $$PWD/models/ldbobjecttablemodel.cpp \
    $$PWD/models/queryparamtablemodel.cpp \
    $$PWD/core/dependencycontainer.cpp \
    $$PWD/models/unisqltablemodel.cpp \
    $$PWD/core/qknowledgebase.cpp \
#Forms
    $$PWD/forms/abstractdatabaseitemform.cpp \
    $$PWD/forms/tableeditform.cpp \
    $$PWD/forms/checkconstrainteditform.cpp \
    $$PWD/forms/foreignkeyform.cpp \
    $$PWD/forms/procedureeditform.cpp \
    $$PWD/forms/sequenceeditform.cpp \
    $$PWD/forms/triggereditform.cpp \
    $$PWD/forms/uniqueconstrainteditform.cpp \
    $$PWD/forms/vieweditdialog.cpp \
    $$PWD/forms/connectioneditdialog.cpp \
    $$PWD/objects/sdkplugin.cpp \
#Utils
    $$PWD/utils/qsqlqueryhelper.cpp \
    $$PWD/tools/qsqlsyntaxhighlighter.cpp \
    $$PWD/utils/eventinterceptors.cpp \
    $$PWD/utils/qfileutils.cpp \
    $$PWD/utils/qsimpletooltip.cpp \
#Models
    $$PWD/models/simplecachedtablemodel.cpp \
    $$PWD/models/comboboxitemdelegate.cpp \
    $$PWD/models/lcachedtablemodel.cpp \
    $$PWD/models/lsqltablemodel.cpp \
    $$PWD/models/qstructureitemmodel.cpp \
    $$PWD/models/tablerowmodel.cpp \
    $$PWD/models/variantmaptablemodel.cpp \
    $$PWD/models/ldbobjectmodel.cpp \
    $$PWD/models/qactiveconnectionmodel.cpp \
    $$PWD/models/lstandardtreemodel.cpp \
    $$PWD/tools/ldatawidgetmapper.cpp \
    $$PWD/models/sqlcolumnmodel.cpp \
    $$PWD/models/comboboxhashdelegate.cpp \
#Base DB classes
    $$PWD/objects/appurl.cpp \
    $$PWD/objects/dbobjectitem.cpp \
    $$PWD/objects/dbdatabaseitem.cpp \
    $$PWD/objects/dbtableitem.cpp \
    $$PWD/objects/dbsequenceitem.cpp \
    $$PWD/objects/dbtriggeritem.cpp \
    $$PWD/objects/dbprocedureitem.cpp \
    $$PWD/objects/dbviewitem.cpp \
    $$PWD/objects/foldertreeitem.cpp \
    $$PWD/objects/dbcheckconstraint.cpp \
    $$PWD/objects/dbconstraintitem.cpp \
    $$PWD/objects/dbforeignkey.cpp \
    $$PWD/objects/dbprimarykey.cpp \
    $$PWD/objects/dbuniqueconstraint.cpp \
    $$PWD/utils/sqlfiltermanager.cpp \
    $$PWD/utils/sqlutils.cpp \
    $$PWD/utils/strutils.cpp

HEADERS  += \
#Core
    $$PWD/core/core.h \
    $$PWD/core/datastore.h \
    $$PWD/core/localeventnotifier.h \
    $$PWD/core/maphelplookupprovider.h \
    $$PWD/core/sqlhelplookupprovider.h \
    $$PWD/core/appsettings.h \
    $$PWD/core/iocplugin.h \
    $$PWD/objects/dbmsplugin.h \
    $$PWD/objects/dbselectableitem.h \
    $$PWD/forms/queryparamsform.h \
    $$PWD/abstractplugin.h \
    $$PWD/core/dependencycontainer.h \
    $$PWD/tools/ltextcompleter.h \
    $$PWD/models/jointdbojbectmodel.h \
    $$PWD/models/ldbobjecttablemodel.h \
    $$PWD/models/queryparamtablemodel.h \
    $$PWD/models/unisqltablemodel.h \
    $$PWD/core/qknowledgebase.h \
#Forms
    $$PWD/forms/abstractdatabaseitemform.h \
    $$PWD/forms/tableeditform.h \
    $$PWD/forms/checkconstrainteditform.h \
    $$PWD/forms/foreignkeyform.h \
    $$PWD/forms/procedureeditform.h \
    $$PWD/forms/sequenceeditform.h \
    $$PWD/forms/triggereditform.h \
    $$PWD/forms/uniqueconstrainteditform.h \
    $$PWD/forms/vieweditdialog.h \
    $$PWD/forms/connectioneditdialog.h \
    $$PWD/objects/sdkplugin.h \
#Utils
    $$PWD/utils/qsqlqueryhelper.h \
    $$PWD/tools/qsqlsyntaxhighlighter.h \
    $$PWD/utils/eventinterceptors.h \
    $$PWD/utils/qfileutils.h \
    $$PWD/utils/qsimpletooltip.h \
#Models
    $$PWD/models/simplecachedtablemodel.h \
    $$PWD/models/comboboxitemdelegate.h \
    $$PWD/models/lcachedtablemodel.h \
    $$PWD/models/lsqltablemodel.h \
    $$PWD/models/qstructureitemmodel.h \
    $$PWD/models/tablerowmodel.h \
    $$PWD/models/variantmaptablemodel.h \
    $$PWD/models/ldbobjectmodel.h \
    $$PWD/models/qactiveconnectionmodel.h \
    $$PWD/models/lstandardtreemodel.h \
    $$PWD/tools/ldatawidgetmapper.h \
    $$PWD/models/sqlcolumnmodel.h \
    $$PWD/models/comboboxhashdelegate.h \
#Base DB classes
    $$PWD/objects/appconst.h \
    $$PWD/objects/appurl.h \
    $$PWD/objects/dbobjectitem.h \
    $$PWD/objects/dbdatabaseitem.h \
    $$PWD/objects/dbtableitem.h \
    $$PWD/objects/dbsequenceitem.h \
    $$PWD/objects/dbtriggeritem.h \
    $$PWD/objects/dbprocedureitem.h \
    $$PWD/objects/dbviewitem.h \
    $$PWD/objects/foldertreeitem.h \
    $$PWD/objects/dbcheckconstraint.h \
    $$PWD/objects/dbconstraintitem.h \
    $$PWD/objects/dbforeignkey.h \
    $$PWD/objects/dbprimarykey.h \
    $$PWD/objects/dbuniqueconstraint.h \
#SQLite
#MySQL
#Postgres
    $$PWD/utils/sqlfiltermanager.h \
    $$PWD/utils/sqlutils.h \
    $$PWD/utils/strutils.h
#Firebird

FORMS    += \
    $$PWD/forms/connectioneditdialog.ui \
    $$PWD/forms/checkconstrainteditform.ui \
    $$PWD/forms/foreignkeyform.ui \
    $$PWD/forms/procedureeditform.ui \
    $$PWD/forms/queryparamsform.ui \
    $$PWD/forms/sequenceeditform.ui \
    $$PWD/forms/triggereditform.ui \
    $$PWD/forms/uniqueconstrainteditform.ui \
    $$PWD/forms/vieweditdialog.ui \
    $$PWD/forms/tableeditform.ui

