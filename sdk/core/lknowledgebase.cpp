#include "lknowledgebase.h"
#include <QDebug>
#include "objects/appconst.h"

void LKnowledgeBase::loadModels(const QStringList &drivers)
{
  foreach(QString driver, drivers) {
    qDebug() << "Load module base:" << driver;
    loadModelByType(T_KEYWORDS, OBJTYPE_KEYWORD, driver);
    loadModelByType(T_FUNCTIONS, OBJTYPE_FUNCTION, driver);
    loadTypeModel(driver);
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

  for(int row=0; row<_mTypes->rowCount(); row++) {
    QSqlRecord rec = _mTypes->record(row);
    if (rec.value(F_DRIVER).toString() == dbms.toUpper())
      resHash.insert(rec.value(F_ID).toInt(), rec.value(F_NAME).toString());
  }
  return resHash;
}

QString LKnowledgeBase::typeName(int type)
{
  if (type <= 0)
    return "Undefined";
  QSqlRecord* rec = _mTypes->recordById(type);
  if (!rec)
    return "Unknown";
  return rec->value(F_NAME).toString();
}

int LKnowledgeBase::typeByName(QString dbms, QString name)
{
  for(int row=0; row<_mTypes->rowCount(); row++) {
    QSqlRecord rec = _mTypes->record(row);
    if (rec.value(F_DBMS).toString() == dbms && rec.value(F_NAME).toString() == name)
      return rec.value(F_ID).toInt();
  }
  //Here should be const
  return 0;
}

void LKnowledgeBase::loadTypeModel(QString driver)
{
  QString sqlPattern = "select * from t_types where driver='%1'";
  QString preparedSql = sqlPattern.arg(driver);

  LDBObjectTableModel* model = new LDBObjectTableModel(this);
  model->registerColumn(F_NAME);
  model->registerColumn(F_CAPTION);
  model->registerColumn(F_DESCRIPTION);
  model->registerColumn(F_DOC_LINK);
  model->registerColumn(F_KIND);

  model->setQuery(preparedSql);
  _typesHash.insert(driver, model);

  model->reload();
  qDebug() << "Types" << driver << ":" << model->rowCount();
}

LDBObjectTableModel* LKnowledgeBase::typesByDriver(QString driver)
{
  if (!_typesHash.contains(driver))
    return nullptr;
  return _typesHash.value(driver);
}

LKnowledgeBase::LKnowledgeBase(QObject *parent) : QObject(parent)
{
  qDebug() << "Knowledge base created";

  _mTypes = new LSqlTableModel(this);
  _mTypes->setTable(T_TYPES);
  _mTypes->select();
  qDebug() << _mTypes->rowCount() << "types loaded";
}



LKnowledgeBase::~LKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
