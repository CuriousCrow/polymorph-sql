#ifndef JOINTDBOJBECTMODEL_H
#define JOINTDBOJBECTMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "ldbobjecttablemodel.h"

class JointDBOjbectModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  JointDBOjbectModel(QObject *parent = nullptr);
  void registerColumn(QString colName);
  void addModel(QString name, LDBObjectTableModel* model);
  void clear();

  QVariantMap rowDataByName(QString name, QString modelName = "");
private:
  QStringList _columns;
  QStringList _modelNames;
  QList<LDBObjectTableModel*> _models;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // JOINTDBOJBECTMODEL_H
