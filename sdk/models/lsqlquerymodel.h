#ifndef LSQLQUERYMODEL_H
#define LSQLQUERYMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QSqlQuery>

class LSqlQueryModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  LSqlQueryModel(QObject *parent = nullptr);
  void reload(QSqlQuery &query);
  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
protected:
  virtual void clear();
private:
  QStringList _headers;
  QList<QVariantList> _rows;
  void updateHeaders(const QSqlRecord &rec);

};

#endif // LSQLQUERYMODEL_H
