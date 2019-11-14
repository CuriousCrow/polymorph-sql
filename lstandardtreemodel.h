#ifndef LSTANDARDTREEMODEL_H
#define LSTANDARDTREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>

class LAbstractTreeItem : public QObject
{
  Q_OBJECT
public:
  explicit LAbstractTreeItem(QString name = "", QObject *parent = nullptr);
  ~LAbstractTreeItem();

  bool hasChildren();

  virtual int colCount() = 0;
  virtual QVariant colData(int column, int role) = 0;
  virtual bool setData(int column, QVariant value, int role) = 0;
};


class LStandardTreeModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit LStandardTreeModel(QObject *parent = nullptr);
  ~LStandardTreeModel();

  void addItem(LAbstractTreeItem* item, LAbstractTreeItem* parent = 0);
  void addItem(LAbstractTreeItem* item, QModelIndex parent);
  LAbstractTreeItem* itemByIndex(QModelIndex index) const;
  QModelIndex indexByItem(LAbstractTreeItem* item);

  virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
  virtual QModelIndex parent(const QModelIndex &child) const;
  virtual int rowCount(const QModelIndex &parent) const;
  virtual int columnCount(const QModelIndex &parent) const;
  virtual bool hasChildren(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual bool removeRows(int row, int count, const QModelIndex &parent);
};

#endif // LSTANDARDTREEMODEL_H
