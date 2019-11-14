#ifndef LDBOBJECTMODEL_H
#define LDBOBJECTMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QSqlQuery>
#include <QSqlError>

struct DbObj {
  QString name;
  QString type;
  DbObj(QString name, QString type);
};

class LDBObjectModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  LDBObjectModel(QObject* parent = nullptr);
  void reload(QStringList keywords, QString connName);
private:
  QList<DbObj> _dataList;
public:
  virtual int rowCount(const QModelIndex &parent) const;
  virtual int columnCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
};

#endif // LDBOBJECTMODEL_H
