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

QKnowledgeBase::QKnowledgeBase(QObject *parent) : QObject(parent)
{
  qDebug() << "Knowledge base created";
  mKeywords = new LSqlTableModel(this);
  mKeywords->setTable(T_KEYWORDS);
  mKeywords->select();
  qDebug() << mKeywords->rowCount() << "keywords loaded";
}

QKnowledgeBase::~QKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
