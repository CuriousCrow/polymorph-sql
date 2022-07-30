#include "lknowledgebase.h"
#include <QDebug>
#include "objects/appconst.h"

void LKnowledgeBase::loadModels(const QStringList &drivers)
{
  foreach(QString driver, drivers) {
    qDebug() << "Load module base:" << driver;
    loadModelByType(T_KEYWORDS, OBJTYPE_KEYWORD, driver);
    loadModelByType(T_FUNCTIONS, OBJTYPE_FUNCTION, driver);
  }
  loadModelByType(T_KEYWORDS, OBJTYPE_KEYWORD);
  loadModelByType(T_FUNCTIONS, OBJTYPE_FUNCTION);
}

LDBObjectTableModel *LKnowledgeBase::modelByType(QString type, QString driver)
{
  QString name = type + driver;
  return _modelHash.value(name);
}

void LKnowledgeBase::loadModelByType(QString table, QString type, QString driver)
{
  QString name = type + driver;
  QString sqlPattern = "select * from %1 where %2";
  QString preparedSql = sqlPattern.arg(table, driver.isEmpty() ? "driver is null" : "driver='" + driver + "'");

  LDBObjectTableModel* model = new LDBObjectTableModel(this);
  model->registerColumn(F_NAME);
  model->registerColumn(F_TYPE);
  model->registerColumn(F_DESCRIPTION);
  model->registerColumn(F_DOC_LINK);
  model->registerColumn(F_DRIVER_NAME);

  model->setFixedValue(F_TYPE, type);
  model->setFixedValue(F_DRIVER_NAME, driver);

  model->setQuery(preparedSql);
  _modelHash.insert(name, model);

  model->reload();
  qDebug() << name << ":" << model->rowCount();
}

QHash<int, QString> LKnowledgeBase::typesHash(QString dbms)
{
  QHash<int, QString> resHash;

  for(int row=0; row<mTypes->rowCount(); row++) {
    QSqlRecord rec = mTypes->record(row);
    if (rec.value(F_DBMS).toString() == dbms.toUpper())
      resHash.insert(rec.value(F_ID).toInt(), rec.value(F_NAME).toString());
  }
  return resHash;
}

QString LKnowledgeBase::typeName(int type)
{
  if (type <= 0)
    return "Undefined";
  QSqlRecord* rec = mTypes->recordById(type);
  if (!rec)
    return "Unknown";
  return rec->value(F_NAME).toString();
}

int LKnowledgeBase::typeByName(QString dbms, QString name)
{
  for(int row=0; row<mTypes->rowCount(); row++) {
    QSqlRecord rec = mTypes->record(row);
    if (rec.value(F_DBMS).toString() == dbms && rec.value(F_NAME).toString() == name)
      return rec.value(F_ID).toInt();
  }
  //Here should be const
  return 0;
}

LKnowledgeBase::LKnowledgeBase(QObject *parent) : QObject(parent)
{
  qDebug() << "Knowledge base created";

  mTypes = new LSqlTableModel(this);
  mTypes->setTable(T_TYPES);
  mTypes->select();
  qDebug() << mTypes->rowCount() << "types loaded";
}



LKnowledgeBase::~LKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
