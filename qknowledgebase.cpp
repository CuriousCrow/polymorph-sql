#include "qknowledgebase.h"
#include <QDebug>
#include "sdk/objects/appconst.h"

QKnowledgeBase* QKnowledgeBase::_kb = nullptr;

QKnowledgeBase *QKnowledgeBase::kb(QObject *parent)
{
  if (!_kb){
    _kb = new QKnowledgeBase(parent);
  }
  return _kb;
}

void QKnowledgeBase::loadModels(const QStringList &drivers)
{
  foreach(QString driver, drivers) {
    qDebug() << "Load module base:" << driver;
    loadModelByType(T_KEYWORDS, OBJTYPE_KEYWORD, driver);
    loadModelByType(T_FUNCTIONS, OBJTYPE_FUNCTION, driver);
  }
  loadModelByType(T_KEYWORDS, OBJTYPE_KEYWORD);
  loadModelByType(T_FUNCTIONS, OBJTYPE_FUNCTION);
}

LDBObjectTableModel *QKnowledgeBase::modelByType(QString type, QString driver)
{
  QString name = type + driver;
  return _modelHash.value(name);
}

void QKnowledgeBase::loadModelByType(QString table, QString type, QString driver)
{
  QString name = type + driver;
  QString sqlPattern = "select * from %1 where %2";
  QString preparedSql = sqlPattern.arg(table).arg(driver.isEmpty() ? "driver is null" : "driver='" + driver + "'");

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

QHash<int, QString> QKnowledgeBase::typesHash(QString dbms)
{
  QHash<int, QString> resHash;

  for(int row=0; row<mTypes->rowCount(); row++) {
    QSqlRecord rec = mTypes->record(row);
    if (rec.value(F_DBMS).toString() == dbms.toUpper())
      resHash.insert(rec.value(F_ID).toInt(), rec.value(F_NAME).toString());
  }
  return resHash;
}

QString QKnowledgeBase::typeName(int type)
{
  if (type <= 0)
    return "Undefined";
  QSqlRecord* rec = mTypes->recordById(type);
  if (!rec)
    return "Unknown";
  return rec->value(F_NAME).toString();
}

int QKnowledgeBase::typeByName(QString dbms, QString name)
{
  for(int row=0; row<mTypes->rowCount(); row++) {
    QSqlRecord rec = mTypes->record(row);
    if (rec.value(F_DBMS).toString() == dbms && rec.value(F_NAME).toString() == name)
      return rec.value(F_ID).toInt();
  }
  //Here should be const
  return 0;
}

QKnowledgeBase::QKnowledgeBase(QObject *parent) : QObject(parent)
{
  qDebug() << "Knowledge base created";
  mKeywords = new LSqlTableModel(this);
  mKeywords->setTable(T_KEYWORDS);
  mKeywords->select();
  qDebug() << mKeywords->rowCount() << "keywords loaded";

  mFunctions = new LSqlTableModel(this);
  mFunctions->setTable(T_FUNCTIONS);
  mFunctions->select();
  qDebug() << mFunctions->rowCount() << "functions loaded";

  mTypes = new LSqlTableModel(this);
  mTypes->setTable(T_TYPES);
  mTypes->select();
  qDebug() << mTypes->rowCount() << "types loaded";
}



QKnowledgeBase::~QKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
