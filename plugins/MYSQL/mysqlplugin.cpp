#include "mysqlplugin.h"
#include "objects/appconst.h"
#include "objects/mysqldatabase.h"
#include "objects/mysqltable.h"
#include "objects/mysqlfolderitem.h"
#include "objects/dbsequence.h"
#include "objects/dbview.h"
#include "objects/dbprocedure.h"
#include "objects/dbtrigger.h"
#include "objects/typeprovider.h"
#include "objects/mysqlview.h"
#include "objects/mysqlsequence.h"
#include "objects/mysqlprocedure.h"
#include "objects/mysqlprimarykey.h"
#include "objects/mysqlforeignkey.h"
#include "objects/mysqluniqueconstraint.h"
#include "objects/mysqlcheckconstraint.h"
#include "objects/mysqltrigger.h"
#include "forms/simplesequenceeditform.h"
#include "forms/mysqlprocedureeditform.h"
#include "forms/mysqltriggerform.h"
#include "mysqlconst.h"


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
  c->registerDependency(new DependencyMeta(B_MYSQL_DATABASE, CLASSMETA(MysqlDatabase), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Database);
  c->registerDependency(new DependencyMeta(B_MYSQL_FOLDER, CLASSMETA(MysqlFolderItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Folder);
  c->registerDependency(new DependencyMeta(B_MYSQL_TABLE, CLASSMETA(MysqlTableItem), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Table);
  c->registerDependency(new DependencyMeta(B_MYSQL_SEQUENCE, CLASSMETA(MysqlSequence), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Sequence);
  c->registerDependency(new DependencyMeta(B_MYSQL_VIEW, CLASSMETA(MysqlView), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::View);
  c->registerDependency(new DependencyMeta(B_MYSQL_PROCEDURE, CLASSMETA(MysqlProcedure), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta(B_MYSQL_TRIGGER, CLASSMETA(MysqlTrigger), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Trigger);

  c->registerDependency(new DependencyMeta(B_MYSQL_PK, CLASSMETA(MysqlPrimaryKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
  c->registerDependency(new DependencyMeta(B_MYSQL_FK, CLASSMETA(MysqlForeignKey), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::ForeignKey);
  c->registerDependency(new DependencyMeta(B_MYSQL_UNIQUE, CLASSMETA(MysqlUniqueConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
  c->registerDependency(new DependencyMeta(B_MYSQL_CHECK, CLASSMETA(MysqlCheckConstraint), InstanceMode::Prototype))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::CheckConstraint);

  c->registerDependency(new DependencyMeta(B_MYSQL_SEQUENCE_FORM, CLASSMETA(SimpleSequenceEditForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Sequence);
  c->registerDependency(new DependencyMeta(B_MYSQL_PROCEDURE_FORM, CLASSMETA(MysqlProcedureEditForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Procedure);
  c->registerDependency(new DependencyMeta(B_MYSQL_TRIGGER_FORM, CLASSMETA(MysqlTriggerForm), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL)->setParam(F_TYPE, DBObjectItem::Trigger);

  c->registerDependency(new DependencyMeta(B_MYSQL_TYPE_PROVIDER, CLASSMETA(BaseTypeProvider), InstanceMode::Singleton))
                        ->setParam(F_DRIVER_NAME, DRIVER_MYSQL);
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
