#include "qknowledgebase.h"
#include <QDebug>
#include "dbms/appconst.h"

QKnowledgeBase* QKnowledgeBase::_kb = nullptr;

QKnowledgeBase *QKnowledgeBase::kb(QObject *parent)
{
  if (!_kb){
    _kb = new QKnowledgeBase(parent);
  }
  return _kb;
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

  mTypes = new LSqlTableModel(this);
  mTypes->setTable(T_TYPES);
  mTypes->select();
  qDebug() << mTypes->rowCount() << "types loaded";
}



QKnowledgeBase::~QKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
