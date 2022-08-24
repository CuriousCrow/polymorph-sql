INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QT += sql widgets

# Enable very detailed debug messages when compiling the debug version
CONFIG(debug, debug|release) {
    DEFINES += SUPERVERBOSE
}

SOURCES += \
#Core
  $$PWD/actions/queryeditorkeysequences.cpp \
  $$PWD/actions/removetablefilteraction.cpp \
  $$PWD/actions/switchconnectedaction.cpp \
    $$PWD/core/abstractcontextaction.cpp \
    $$PWD/core/abstractusercontext.cpp \
    $$PWD/core/basecontextaction.cpp \
    $$PWD/core/baseusercontext.cpp \
    $$PWD/core/core.cpp \
    $$PWD/core/datastore.cpp \
    $$PWD/core/extensions.cpp \
    $$PWD/core/localeventnotifier.cpp \
    $$PWD/core/maphelplookupprovider.cpp \
    $$PWD/core/sqlhelplookupprovider.cpp \
    $$PWD/core/appsettings.cpp \
    $$PWD/core/iocplugin.cpp \
    $$PWD/core/dependencycontainer.cpp \
    $$PWD/core/lknowledgebase.cpp \
#Forms
  $$PWD/extensions/unisqltablefilteraction.cpp \
    $$PWD/forms/queryparamsform.cpp \
    $$PWD/forms/abstractdatabaseitemform.cpp \
    $$PWD/forms/simplesequenceeditform.cpp \
    $$PWD/forms/tableeditform.cpp \
    $$PWD/forms/checkconstrainteditform.cpp \
    $$PWD/forms/foreignkeyform.cpp \
    $$PWD/forms/procedureeditform.cpp \
    $$PWD/forms/sequenceeditform.cpp \
    $$PWD/forms/triggereditform.cpp \
    $$PWD/forms/uniqueconstrainteditform.cpp \
    $$PWD/forms/vieweditdialog.cpp \
    $$PWD/forms/connectioneditdialog.cpp \
    $$PWD/forms/databaseexportform.cpp \
    $$PWD/forms/queryhistoryform.cpp \
    $$PWD/forms/settingsform.cpp \
    $$PWD/forms/queryeditorwindow.cpp \
    $$PWD/forms/tablebrowserwindow.cpp \
#Widgets
  $$PWD/objects/abstractidentifiersupport.cpp \
  $$PWD/objects/dbusertype.cpp \
  $$PWD/tools/keysequenceinterceptor.cpp \
  $$PWD/tools/simplesqlcompletersupport.cpp \
  $$PWD/tools/sqleditorsupport.cpp \
  $$PWD/tools/testclasses.cpp \
  $$PWD/utils/messagedialogs.cpp \
    $$PWD/widgets/blobeditor.cpp \
    $$PWD/widgets/itemviewer.cpp \
    $$PWD/widgets/lqueryeditor.cpp \
    $$PWD/widgets/tablebrowserdelegate.cpp \
#Tools
    $$PWD/tools/lsqlsyntaxhighlighter.cpp \
    $$PWD/tools/ltextcompleter.cpp \
    $$PWD/tools/ldatawidgetmapper.cpp \
#Utils
    $$PWD/utils/sqlqueryhelper.cpp \
    $$PWD/utils/eventinterceptors.cpp \
    $$PWD/utils/fileutils.cpp \
    $$PWD/utils/lsimpletooltip.cpp \
    $$PWD/utils/sqlfiltermanager.cpp \
    $$PWD/utils/sqlutils.cpp \
    $$PWD/utils/strutils.cpp \
#Models
    $$PWD/models/unisqltablemodel.cpp \
    $$PWD/models/jointdbojbectmodel.cpp \
    $$PWD/models/ldbobjecttablemodel.cpp \
    $$PWD/models/queryparamtablemodel.cpp \
    $$PWD/models/simplecachedtablemodel.cpp \
    $$PWD/models/comboboxitemdelegate.cpp \
    $$PWD/models/lcachedtablemodel.cpp \
    $$PWD/models/lsqltablemodel.cpp \
    $$PWD/models/lstructureitemmodel.cpp \
    $$PWD/models/tablerowmodel.cpp \
    $$PWD/models/variantmaptablemodel.cpp \
    $$PWD/models/ldbobjectmodel.cpp \
    $$PWD/models/lactiveconnectionmodel.cpp \
    $$PWD/models/lstandardtreemodel.cpp \
    $$PWD/models/sqlcolumnmodel.cpp \
    $$PWD/models/comboboxhashdelegate.cpp \
#Actions
    $$PWD/actions/addnewqueryeditoraction.cpp \
    $$PWD/actions/dropitemobjectaction.cpp \
    $$PWD/actions/exportddltoclipboardaction.cpp \
    $$PWD/actions/exportdmltoclipboardaction.cpp \
    $$PWD/actions/reloadfolderitemsaction.cpp \
    $$PWD/actions/showcreateformaction.cpp \
    $$PWD/actions/showdatabaseexporteditoraction.cpp \
    $$PWD/actions/showitemeditoraction.cpp \
    $$PWD/actions/showsettingsformaction.cpp \
#Base DB classes
    $$PWD/objects/dbselectableitem.cpp \
    $$PWD/objects/sdkplugin.cpp \
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
    $$PWD/objects/dbuniqueconstraint.cpp

HEADERS  += \
    $$PWD/abstractplugin.h \
#Core
  $$PWD/actions/queryeditorkeysequences.h \
  $$PWD/actions/removetablefilteraction.h \
  $$PWD/actions/switchconnectedaction.h \
    $$PWD/core/abstractcontextaction.h \
    $$PWD/core/abstractusercontext.h \
    $$PWD/core/basecontextaction.h \
    $$PWD/core/baseusercontext.h \
    $$PWD/core/core.h \
    $$PWD/core/datastore.h \
  $$PWD/core/extensionpoints.h \
    $$PWD/core/extensions.h \
    $$PWD/core/localeventnotifier.h \
    $$PWD/core/maphelplookupprovider.h \
    $$PWD/core/sqlhelplookupprovider.h \
    $$PWD/core/appsettings.h \
    $$PWD/core/iocplugin.h \
    $$PWD/core/dependencycontainer.h \
    $$PWD/core/lknowledgebase.h \
#Forms
  $$PWD/extensions/unisqltablefilteraction.h \
    $$PWD/forms/queryparamsform.h \
    $$PWD/forms/abstractdatabaseitemform.h \
    $$PWD/forms/simplesequenceeditform.h \
    $$PWD/forms/tableeditform.h \
    $$PWD/forms/checkconstrainteditform.h \
    $$PWD/forms/foreignkeyform.h \
    $$PWD/forms/procedureeditform.h \
    $$PWD/forms/sequenceeditform.h \
    $$PWD/forms/triggereditform.h \
    $$PWD/forms/uniqueconstrainteditform.h \
    $$PWD/forms/vieweditdialog.h \
    $$PWD/forms/connectioneditdialog.h \
    $$PWD/forms/queryhistoryform.h \
    $$PWD/forms/settingsform.h \
    $$PWD/forms/databaseexportform.h \
    $$PWD/forms/queryeditorwindow.h \
    $$PWD/forms/tablebrowserwindow.h \
#Widgets
  $$PWD/objects/abstractidentifiersupport.h \
  $$PWD/objects/dbusertype.h \
  $$PWD/tools/keysequenceinterceptor.h \
  $$PWD/tools/simplesqlcompletersupport.h \
  $$PWD/tools/sqleditorsupport.h \
  $$PWD/tools/testclasses.h \
  $$PWD/utils/messagedialogs.h \
    $$PWD/widgets/blobeditor.h \
    $$PWD/widgets/itemviewer.h \
    $$PWD/widgets/lqueryeditor.h \
    $$PWD/widgets/tablebrowserdelegate.h \
#Tools
    $$PWD/tools/ldatawidgetmapper.h \
    $$PWD/tools/ltextcompleter.h \
    $$PWD/tools/lsqlsyntaxhighlighter.h \
#Utils
    $$PWD/utils/sqlqueryhelper.h \
    $$PWD/utils/eventinterceptors.h \
    $$PWD/utils/fileutils.h \
    $$PWD/utils/lsimpletooltip.h \
    $$PWD/utils/sqlfiltermanager.h \
    $$PWD/utils/sqlutils.h \
    $$PWD/utils/strutils.h \
#Models
    $$PWD/models/jointdbojbectmodel.h \
    $$PWD/models/ldbobjecttablemodel.h \
    $$PWD/models/queryparamtablemodel.h \
    $$PWD/models/unisqltablemodel.h \
    $$PWD/models/simplecachedtablemodel.h \
    $$PWD/models/comboboxitemdelegate.h \
    $$PWD/models/lcachedtablemodel.h \
    $$PWD/models/lsqltablemodel.h \
    $$PWD/models/lstructureitemmodel.h \
    $$PWD/models/tablerowmodel.h \
    $$PWD/models/variantmaptablemodel.h \
    $$PWD/models/ldbobjectmodel.h \
    $$PWD/models/lactiveconnectionmodel.h \
    $$PWD/models/lstandardtreemodel.h \
    $$PWD/models/sqlcolumnmodel.h \
    $$PWD/models/comboboxhashdelegate.h \
#Actions
    $$PWD/actions/addnewqueryeditoraction.h \
    $$PWD/actions/dropitemobjectaction.h \
    $$PWD/actions/exportddltoclipboardaction.h \
    $$PWD/actions/exportdmltoclipboardaction.h \
    $$PWD/actions/reloadfolderitemsaction.h \
    $$PWD/actions/showcreateformaction.h \
    $$PWD/actions/showdatabaseexporteditoraction.h \
    $$PWD/actions/showitemeditoraction.h \
    $$PWD/actions/showsettingsformaction.h \
#Base DB classes
    $$PWD/objects/sdkplugin.h \
    $$PWD/objects/dbmsplugin.h \
    $$PWD/objects/dbselectableitem.h \
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
    $$PWD/objects/dbuniqueconstraint.h

FORMS    += \
    $$PWD/forms/connectioneditdialog.ui \
    $$PWD/forms/checkconstrainteditform.ui \
    $$PWD/forms/foreignkeyform.ui \
    $$PWD/forms/procedureeditform.ui \
    $$PWD/forms/queryparamsform.ui \
    $$PWD/forms/sequenceeditform.ui \
    $$PWD/forms/simplesequenceeditform.ui \
    $$PWD/forms/triggereditform.ui \
    $$PWD/forms/uniqueconstrainteditform.ui \
    $$PWD/forms/vieweditdialog.ui \
    $$PWD/forms/tableeditform.ui \
    $$PWD/forms/queryhistoryform.ui \
    $$PWD/forms/settingsform.ui \
    $$PWD/forms/databaseexportform.ui \
    $$PWD/forms/queryeditorwindow.ui \
    $$PWD/widgets/itemviewer.ui \
    $$PWD/widgets/blobeditor.ui \
    $$PWD/forms/tablebrowserwindow.ui

TRANSLATIONS += \
    $$PWD/translations/sdk_ru.ts

RESOURCES += \
    $$PWD/icons.qrc
