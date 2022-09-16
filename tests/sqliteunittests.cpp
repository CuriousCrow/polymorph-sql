#include "sqliteunittests.h"
#include <QDebug>
#include "sqliteplugin.h"
#include "objects/sqliteviewitem.h"
#include "objects/sqlitetable.h"
#include "models/sqlcolumnmodel.h"
#include "core/datastore.h"
#include "core/lknowledgebase.h"
#include "objects/sdkplugin.h"

SqliteUnitTests::SqliteUnitTests(QObject *parent) : QObject(parent)
{
  _core = Core::instance(this);
  DataStore* ds = new DataStore(this);
  LKnowledgeBase* kb = new LKnowledgeBase(this);
  _core->registerSingletonObject(new DependencyMeta(B_DATA_STORE, CLASSMETA(DataStore)), ds);
  _core->registerSingletonObject(new DependencyMeta(B_KNOWLEDGE_BASE, CLASSMETA(LKnowledgeBase)), kb);
}

SqliteUnitTests::~SqliteUnitTests()
{
}

void SqliteUnitTests::initTestCase()
{
  qDebug() << "Testing environment setup";

  _core->registerPlugin(new SqlitePlugin());
  _core->registerDependency(B_BASE_COLUMN_MODEL, CLASSMETA(SqlColumnModel), InstanceMode::Prototype);
}

void SqliteUnitTests::cleanupTestCase()
{
}

void SqliteUnitTests::sqliteViewTest()
{
  SqliteViewItem* view = static_cast<SqliteViewItem*>(_core->newObjInstance(DRIVER_SQLITE, DBObjectItem::View));
  view->setFieldValue(F_CAPTION, "testview");
  view->setFieldValue(F_QUERY_TEXT, "select * from city");
  QString ddlActual = view->toDDL();
  QString ddlExpected = "create view \"testview\" as select * from city";
  QCOMPARE(ddlActual, ddlExpected);
}

void SqliteUnitTests::sqliteTableTest()
{
  SqliteTableItem* table = static_cast<SqliteTableItem*>(_core->newObjInstance(DRIVER_SQLITE, DBObjectItem::Table));
  table->setFieldValue(F_CAPTION, "testtable");
  table->columnsModel()->addSqlColumn(SqlColumn("ID", "INTEGER"));
  table->columnsModel()->addSqlColumn(SqlColumn("NAME", "TEXT"));
  QString ddlExprected = "CREATE TABLE testtable (ID INTEGER, NAME TEXT);";
  QCOMPARE(table->toDDL(), ddlExprected);
}

QTEST_MAIN(SqliteUnitTests)
