#ifndef QDBMYSQLITEM_H
#define QDBMYSQLITEM_H

#include "qdbdatabaseitem.h"

class QDBMysqlItem : public QDBDatabaseItem
{
  Q_OBJECT
public:
  QDBMysqlItem(QString caption, QObject* parent = 0);
  ~QDBMysqlItem();

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
};

#endif // QDBMYSQLITEM_H
