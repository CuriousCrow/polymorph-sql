#ifndef TABLEROWMODEL_H
#define TABLEROWMODEL_H

#include <QAbstractTableModel>
#include "dbms/qdbobjectitem.h"
#include <QSqlRecord>


class QDBFieldItem : public QDBObjectItem
{
  Q_OBJECT
public:
  QDBFieldItem(QString caption, QObject* parent = 0);
};

class TableRowModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  TableRowModel(QObject *parent = Q_NULLPTR);
  void setTableItem(QDBObjectItem* item);
  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent) const;
  virtual int columnCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
private:
  QDBObjectItem* _tableItem;
  QSqlRecord _infoRec;

  // QAbstractItemModel interface
public:
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};
#endif // TABLEROWMODEL_H
