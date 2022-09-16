#include "postgresunittests.h"
#include <QDebug>
#include "postgresplugin.h"
#include "objects/postgresviewitem.h"
#include "objects/postgrestable.h"
#include "objects/postgresprimarykey.h"
#include "models/sqlcolumnmodel.h"
#include "core/datastore.h"
#include "core/lknowledgebase.h"
#include "objects/sdkplugin.h"

PostgresUnitTests::PostgresUnitTests(QObject *parent) : QObject(parent)
{
  _core = Core::instance(this);
  DataStore* ds = new DataStore(this);
  LKnowledgeBase* kb = new LKnowledgeBase(this);
  _core->registerSingletonObject(new DependencyMeta(B_DATA_STORE, CLASSMETA(DataStore)), ds);
  _core->registerSingletonObject(new DependencyMeta(B_KNOWLEDGE_BASE, CLASSMETA(LKnowledgeBase)), kb);
}

PostgresUnitTests::~PostgresUnitTests()
{
}

void PostgresUnitTests::initTestCase()
{
  qDebug() << "Testing environment setup";

  _core->registerPlugin(new PostgresPlugin());
  _core->registerDependency(B_BASE_COLUMN_MODEL, CLASSMETA(SqlColumnModel), InstanceMode::Prototype);
}

void PostgresUnitTests::cleanupTestCase()
{
}

void PostgresUnitTests::postgresViewTest()
{
  PostgresViewItem* view = static_cast<PostgresViewItem*>(_core->newObjInstance(DRIVER_POSTGRES, DBObjectItem::View));
  view->setFieldValue(F_CAPTION, "testview");
  view->setFieldValue(F_QUERY_TEXT, "select * from city");
  QString ddlActual = view->toDDL();
  QString ddlExpected = "create view \"testview\" as select * from city";
  QCOMPARE(ddlActual, ddlExpected);
}

void PostgresUnitTests::postgresTableTest()
{
  PostgresTable* table = static_cast<PostgresTable*>(_core->newObjInstance(DRIVER_POSTGRES, DBObjectItem::Table));
  table->setFieldValue(F_CAPTION, "testtable");
  table->columnsModel()->addSqlColumn(SqlColumn("ID", "INTEGER"));
  table->columnsModel()->addSqlColumn(SqlColumn("NAME", "VARCHAR"));
  QString ddlExprected = "CREATE TABLE \"testtable\" (ID INTEGER, NAME VARCHAR);";
  QCOMPARE(table->toDDL(), ddlExprected);
}

void PostgresUnitTests::postgresPrimaryKeyTest()
{
  PostgresPrimaryKey* pk = static_cast<PostgresPrimaryKey*>(_core->newObjInstance(DRIVER_POSTGRES, DBObjectItem::PrimaryKey));
  pk->setFieldValue(F_CAPTION, "pk_tabletest");
  pk->setFieldValue(F_TABLE, "testtable");
  pk->setFieldValue(F_COLUMN, "id");
  QString ddlExprected = "alter table \"testtable\" add constraint pk_tabletest primary key (id)";
  QCOMPARE(pk->toDDL(), ddlExprected);
}

QTEST_MAIN(PostgresUnitTests)
