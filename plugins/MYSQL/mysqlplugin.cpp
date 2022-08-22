#include "mysqlplugin.h"
#include "objects/appconst.h"
#include "mysqldatabase.h"
#include "mysqltable.h"
#include "mysqlfolderitem.h"
#include "objects/dbsequenceitem.h"
#include "objects/dbviewitem.h"
#include "objects/dbprocedureitem.h"
#include "objects/dbtriggeritem.h"
#include "forms/simplesequenceeditform.h"
#include "mysqlview.h"
#include "mysqlsequence.h"
#include "mysqlprocedure.h"
#include "mysqlprimarykey.h"
#include "mysqlforeignkey.h"
#include "mysqluniqueconstraint.h"
#include "mysqlcheckconstraint.h"
#include "mysqlprocedureeditform.h"
#include "mysqltriggerform.h"
#include "mysqltrigger.h"


MysqlPlugin::MysqlPlugin(QObject *parent) : IocPlugin(parent)
{

}

QList<DBObjectItem::ItemType> MysqlPlugin::supportedTypes()
{
  QList<DBObjectItem::ItemType> types;
  types.append(DBObjectItem::Table);
  types.append(DBObjectItem::View);
  types.append(DBObjectItem::SystemTable);
  types.append(DBObjectItem::Sequence);
  types.append(DBObjectItem::Procedure);
  types.append(DBObjectItem::Trigger);
  return types;
}

bool MysqlPlugin::registerPlugin(DependencyContainer *c)
{
  c->registerDependency(new DependencyMeta("mysqlDatabaseItem", CLASSMETA(MysqlDatabase), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Database);
  c->registerDependency(new DependencyMeta("mysqlFolderItem", CLASSMETA(MysqlFolderItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Folder);
  c->registerDependency(new DependencyMeta("mysqlTableItem", CLASSMETA(MysqlTableItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Table);
  c->registerDependency(new DependencyMeta("mysqlSequenceItem", CLASSMETA(MysqlSequence), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Sequence);
  c->registerDependency(new DependencyMeta("mysqlView", CLASSMETA(MysqlView), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::View);
  c->registerDependency(new DependencyMeta("mysqlProcedure", CLASSMETA(MysqlProcedure), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta("mysqlTrigger", CLASSMETA(MysqlTrigger), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Trigger);

  c->registerDependency(new DependencyMeta("mysqlPrimaryKey", CLASSMETA(MysqlPrimaryKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
  c->registerDependency(new DependencyMeta("mysqlForeignKey", CLASSMETA(MysqlForeignKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::ForeignKey);
  c->registerDependency(new DependencyMeta("mysqlUniqueConstraint", CLASSMETA(MysqlUniqueConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
  c->registerDependency(new DependencyMeta("mysqlCheckConstraint", CLASSMETA(MysqlCheckConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::CheckConstraint);

  c->registerDependency(new DependencyMeta("mysqlSequenceForm", CLASSMETA(SimpleSequenceEditForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Sequence);
  c->registerDependency(new DependencyMeta("mysqlProcedureForm", CLASSMETA(MysqlProcedureEditForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta("mysqlTriggerForm", CLASSMETA(MysqlTriggerForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Trigger);
  return true;
}

QString MysqlPlugin::title()
{
    return "MySQL database support plugin";
}

QString MysqlPlugin::author()
{
    return "Lev Alekseevskiy";
}

int MysqlPlugin::majorVersion()
{
    return 1;
}

int MysqlPlugin::minorVersion()
{
    return 0;
}

FeatureTypes MysqlPlugin::featureTypes()
{
    return FeatureType::DbmsObjects;
}

bool MysqlPlugin::driverSupported(QString driverName)
{
    return driverName.toUpper() == DRIVER_MYSQL;
}

QString MysqlPlugin::driver()
{
    return DRIVER_MYSQL;
}
