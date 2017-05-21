#include "qknowledgebase.h"
#include <QDebug>

QKnowledgeBase* QKnowledgeBase::_kb = 0;

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
  mKeywords->setTable("t_keywords");
  mKeywords->select();
  qDebug() << mKeywords->rowCount() << "keywords loaded";
}

QKnowledgeBase::~QKnowledgeBase()
{
  qDebug() << "Knoledge base destroyed";
}
