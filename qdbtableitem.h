#ifndef QDBTABLEITEM_H
#define QDBTABLEITEM_H

#include "qdbobjectitem.h"
#include "models/sqlcolumnmodel.h"


class QDBTableItem : public QDBObjectItem
{
    Q_OBJECT
public:
  QDBTableItem(QString caption, QObject* parent = 0);
  ~QDBTableItem();
  virtual void reloadColumnsModel();
  QAbstractTableModel* columnsModel();
  void addDefaultColumn();
  QHash<int, QString> getColumnTypesHash();

  // QDBObjectItem interface
public:
  virtual bool loadChildren();
  virtual QUrl objectUrl();
  virtual int type();

  // LAbstractTreeItem interface
public:
  virtual int colCount();
  virtual QVariant colData(int column, int role);

  // QDBObjectItem interface
public:
  virtual bool deleteMe();
  virtual bool insertMe();
  virtual bool updateMe();
protected:
  SqlColumnModel* _columnsModel;
};

#endif // QDBTABLEITEM_H
