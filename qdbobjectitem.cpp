#include "qdbobjectitem.h"
#include <QUrl>
#include <QDebug>

#include <QMetaProperty>


QDBObjectItem::QDBObjectItem(QString caption, QObject* parent): LAbstractTreeItem(caption, parent)
{
  _caption = caption;
}

QDBObjectItem::~QDBObjectItem()
{
}

QUrl QDBObjectItem::objectUrl()
{
  if (parent() && parent()->inherits("LAbstractTreeItem"))
    return ((QDBObjectItem*)parent())->objectUrl();
  else
    return QUrl();
}
QString QDBObjectItem::caption() const
{
  return _caption;
}

void QDBObjectItem::setCaption(const QString &caption)
{
  _caption = caption;
}

QStringList QDBObjectItem::propertyList()
{
  QStringList resList = QStringList();
  for(int i=LAbstractTreeItem::staticMetaObject.propertyOffset(); i<metaObject()->propertyCount(); i++){
    resList << metaObject()->property(i).name();
  }
  return resList;
}

void QDBObjectItem::updateObjectName()
{
  QUrl objUrl = objectUrl();
  QString newObjectName = objUrl.url();
  _connectionName = objUrl.host();
//  qDebug() << this << "connection name:" << objUrl.host();
//  qDebug() << this << "new object name:" << newObjectName;
  setObjectName(newObjectName);
  for (int i=0; i<children().count(); i++){
    ((QDBObjectItem*)children().at(i))->updateObjectName();
  }
}

bool QDBObjectItem::setData(int column, QVariant value, int role)
{
  if (role == Qt::EditRole){
    switch (column) {
    case 0:
      setCaption(value.toString());
      break;
    default:
      break;
    }
  }
  return true;
}

bool QDBObjectItem::insertMe(){
  return true;
}

bool QDBObjectItem::updateMe()
{
  return true;
}

bool QDBObjectItem::deleteMe()
{
  return true;
}
