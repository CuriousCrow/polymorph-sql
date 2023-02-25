#include "sdkunittests.h"
#include <QDebug>
#include "models/sqlcolumnmodel.h"
#include "core/datastore.h"
#include "core/lknowledgebase.h"
#include "objects/dbprimarykey.h"
#include "objects/dbuniqueconstraint.h"
#include "objects/dbforeignkey.h"
#include "objects/sdkplugin.h"

SdkUnitTests::SdkUnitTests(QObject *parent) : QObject(parent)
{
    _core = Core::instance(this);
    DataStore* ds = new DataStore(this);
    LKnowledgeBase* kb = new LKnowledgeBase(this);
    _core->registerSingletonObject(new DependencyMeta(B_DATA_STORE, CLASSMETA(DataStore)), ds);
    _core->registerSingletonObject(new DependencyMeta(B_KNOWLEDGE_BASE, CLASSMETA(LKnowledgeBase)), kb);
}

void SdkUnitTests::initTestCase()
{
    qDebug() << "Testing environment setup";

    _core->registerPlugin(new SdkPlugin());
    _core->registerDependency(B_BASE_COLUMN_MODEL, CLASSMETA(SqlColumnModel), InstanceMode::Prototype);
    _core->registerDependency("PrimaryKey", CLASSMETA(DBPrimaryKey), InstanceMode::Prototype)
            ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::PrimaryKey);
    _core->registerDependency("UniqueConstraint", CLASSMETA(DBUniqueConstraint), InstanceMode::Prototype)
            ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::UniqueConstraint);
    _core->registerDependency("ForeignKey", CLASSMETA(DBForeignKey), InstanceMode::Prototype)
            ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::ForeignKey);
    _core->registerDependency("CheckConstraint", CLASSMETA(DBCheckConstraint), InstanceMode::Prototype)
            ->setParam(F_DRIVER_NAME, DRIVER_BASE)->setParam(F_TYPE, DBObjectItem::CheckConstraint);
}

void SdkUnitTests::cleanupTestCase()
{
}

void SdkUnitTests::ViewBasicTest()
{
    auto view = static_cast<DBViewItem*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::View));
    view->setFieldValue(F_CAPTION, "testview");
    view->setFieldValue(F_QUERY_TEXT, "select * from testtable");

    QString ddlExpected = "create view \"testview\" as select * from testtable";
    QCOMPARE(view->toDDL(), ddlExpected);

    ddlExpected = "drop view \"testview\"";
    QCOMPARE(view->dropDDL(), ddlExpected);
}

void SdkUnitTests::TableBasicTest()
{
    auto table = static_cast<DBTableItem*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::Table));
    table->setFieldValue(F_CAPTION, "testtable");

    QString ddlExpected = "drop table \"testtable\"";
    QCOMPARE(table->dropDDL(), ddlExpected);
}

void SdkUnitTests::PrimaryKeyTest()
{
    auto primaryKey = static_cast<DBPrimaryKey*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::PrimaryKey));
    primaryKey->setFieldValue(F_CAPTION, "pk_testtable");
    primaryKey->setFieldValue(F_TABLE, "testtable");
    primaryKey->setFieldValue(F_COLUMN, "id");

    QString ddlExpected = "alter table \"testtable\" add constraint pk_testtable primary key (id)";
    QCOMPARE(primaryKey->toDDL(), ddlExpected);
}

void SdkUnitTests::UniqueConstraintTest()
{
    auto unique = static_cast<DBUniqueConstraint*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::UniqueConstraint));
    unique->setFieldValue(F_CAPTION, "uq_testtable");
    unique->setFieldValue(F_TABLE, "testtable");
    unique->setFieldValue(F_COLUMN, "name");

    QString ddlExpected = "alter table \"testtable\" add constraint uq_testtable unique (name)";
    QCOMPARE(unique->toDDL(), ddlExpected);
}

void SdkUnitTests::ForegnKeyTest()
{
    auto foreignKey = static_cast<DBForeignKey*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::ForeignKey));
    foreignKey->setFieldValue(F_CAPTION, "fk_city_country");
    foreignKey->setFieldValue(F_TABLE, "city");
    foreignKey->setFieldValue(F_COLUMN, "country_id");
    foreignKey->setFieldValue(F_REFTABLE, "country");
    foreignKey->setFieldValue(F_REFCOLUMN, "id");

    foreignKey->setFieldValue(F_ON_UPDATE, "cascade");
    foreignKey->setFieldValue(F_ON_DELETE, "cascade");

    QString ddlExpected = "alter table \"city\" add constraint fk_city_country "
                  "foreign key (country_id) references \"country\"(id) "
                  "on update cascade on delete cascade";
    QCOMPARE(foreignKey->toDDL(), ddlExpected);
}

void SdkUnitTests::CheckConstraintTest()
{
    auto checkConstraint = static_cast<DBCheckConstraint*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::CheckConstraint));
    checkConstraint->setFieldValue(F_CAPTION, "chk_city");
    checkConstraint->setFieldValue(F_TABLE, "city");
    checkConstraint->setFieldValue(F_EXPRESSION, "NAME<>''");

    QString ddlExpected = "alter table \"city\" add constraint chk_city check (NAME<>'')";
    QCOMPARE(checkConstraint->toDDL(), ddlExpected);
}

void SdkUnitTests::ProcedureDropTest()
{
    auto procedureObj = static_cast<DBProcedureItem*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::Procedure));
    procedureObj->setFieldValue(F_CAPTION, "testproc");

    QString ddlExpected = "DROP PROCEDURE testproc";
    QCOMPARE(procedureObj->dropDDL(), ddlExpected);
}

void SdkUnitTests::TableDropTest()
{
    auto tableObj = static_cast<DBTableItem*>(_core->newObjInstance(DRIVER_BASE, DBObjectItem::Table));
    tableObj->setFieldValue(F_CAPTION, "testtable");

    QString ddlExpected = "drop table \"testtable\"";
    QCOMPARE(tableObj->dropDDL(), ddlExpected);
}


QTEST_MAIN(SdkUnitTests)
