#ifndef LDBOBJECTTABLEMODEL_H
#define LDBOBJECTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QSqlDatabase>

class LDBObjectTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  LDBObjectTableModel(QObject *parent = nullptr);
  void setFixedValue(QString name, QVariant value);
  QVariant fixedValue(QString name);
  void registerColumn(QString name);
  void setQuery(QString sql);
  void clear();
  void reload(QString connectionName = QSqlDatabase::defaultConnection);

  QString nameByRow(int row) const;
  QVariantMap rowByName(QString name) const;
  bool contains(QString name) const;

  QVariant data(int row, int column);
  int colByName(QString name) const;
  QString columnName(int idx) const;
private:

  QString _idxField = "name";
  QString _sqlQuery;
  QStringList _columns;
  QVariantMap _fixedValues;
  QStringList _rowIndex;
  QMap<QString, QVariantMap> _dataMap;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // LDBOBJECTTABLEMODEL_H
