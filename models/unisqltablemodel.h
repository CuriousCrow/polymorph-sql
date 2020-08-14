#ifndef UNISQLTABLEMODEL_H
#define UNISQLTABLEMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlIndex>
#include <QSqlField>
#include "../utils/sqlfiltermanager.h"
#include "../utils/sqlutils.h"


class UniSqlTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  UniSqlTableModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase());
  bool setTable(QString tableName);
  bool select();
  bool isDirty();
  bool submitAll(bool stopOnError = true);
  bool submitById(qlonglong id);
  bool revertAll();
  SqlFilterManager* filter();
  QString tableName();
  QString fieldName(int idx);
signals:
  void error(QString message);

protected:
  //TODO: Should be static method
  QVariant execQuery(const QString &sql, QString resColumn);
  //Wrapper for all sql-queries (for debugging)
  bool execQuery(const QString &sql);

  void clearData();

  bool intPk();
  bool noPk();
  bool supportsReturning();
  qlonglong getId(QSqlQuery &query);
  qlonglong genId();
  qlonglong genTempId();
  QSqlRecord recByRow(int row) const;
  qlonglong idByRow(int row) const;
  QString fields();

  virtual QString selectAllSql();
  virtual bool selectRowInTable(QSqlRecord &values);
  virtual bool updateRowInTable(const QSqlRecord &oldValues, const QSqlRecord &newValues);
  virtual bool insertRowInTable(const QSqlRecord &values);
  virtual bool deleteRowInTable(const QSqlRecord &values);
private:
  QString _tableName;
  QSqlIndex _primaryKey;
  QSqlRecord _patternRec;
  QList<qlonglong> _rowIndex;
  QHash<qlonglong, QSqlRecord> _changesHash;
  QHash<qlonglong, QSqlRecord> _dataHash;
  SqlFilterManager* _filterManager;

  QSqlDatabase _db;
  QSqlQuery _query;
  QStringList _sqlErrors;
  qlonglong _genId = 1;
  qlonglong _tempId = -1;
  QString _intPkField;

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
  virtual bool insertRows(int row, int count = 1, const QModelIndex &parent = QModelIndex()) override;
  virtual bool removeRows(int row, int count = 1, const QModelIndex &parent = QModelIndex()) override;
};

#endif // UNISQLTABLEMODEL_H
