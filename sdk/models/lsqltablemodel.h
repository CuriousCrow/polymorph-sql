#ifndef LSQLTABLEMODEL_H
#define LSQLTABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlField>
#include <QSqlIndex>
#include "../utils/sqlfiltermanager.h"
#include "../utils/sqlutils.h"

#define DEBUG_SQL //All queries are shown by qDebug()

class LLookupField;

class LSqlRecord : public QSqlRecord
{
public:
  LSqlRecord();
  LSqlRecord(const QSqlRecord& rec);

  enum CacheAction {None, Insert, Update, Delete};

  void setCacheAction(CacheAction action){ _cacheAction = action; }
  CacheAction cacheAction() const { return _cacheAction; }
private:
  CacheAction _cacheAction;
};


class LSqlTableModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit LSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

  bool setTable(QString tableName);
  QString tableName();
  SqlFilterManager* filter();


  void setSort(int colIndex, Qt::SortOrder sortOrder);
  void setSort(QString colName, Qt::SortOrder sortOrder);

  void setHeaders(QStringList strList);

  void addLookupField(LSqlTableModel* lookupModel, QString keyField, QString lookupField);

  int fieldIndex(QString fieldName) const;
  QString fieldName(int col) const;
  QMetaType::Type fieldType(int col) const;
  bool isDirty(const QModelIndex & index) const;
  bool isDirty() const;
  void setCacheAction(qlonglong recId, LSqlRecord::CacheAction action);

  void setSequenceName(QString name);
  //Populate model with table data
  virtual bool select();
  //Submit one record by row
  bool submitRow(int row);
  //Submit all cached changes to database
  bool submitAll();
  //Revert all cached changes
  bool revertAll();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  int columnCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
  QVariant data(int row, QString columnName, int role = Qt::DisplayRole);
  bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
  bool setData(int row, QString columnName, QVariant value, int role = Qt::EditRole);
  Qt::ItemFlags flags(const QModelIndex & index) const ;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());

  QSqlRecord record(int row) const;
  int rowByValue(QString field, QVariant value);
  QSqlRecord* recordById(qlonglong id);
  QSqlRecord patternRecord() { return _patternRec; }

  //TODO: Should be static method
  QVariant execQuery(const QString &sql, QString resColumn);
  //Wrapper for all sql-queries (for debugging)
  bool execQuery(const QString &sql);
signals:
  void error(QString message);
  void beforeInsert(QSqlRecord &rec);
  void beforeUpdate(QSqlRecord &rec);
private:
  QString _tableName;
  SqlFilterManager* _filterManager;

  QString _orderByClause;
  QString _sequenceName;
  QStringList _headers;

  typedef QHash<qlonglong, LSqlRecord> CacheMap;
  QSqlIndex _primaryIndex;
  QSqlRecord _patternRec;
  QList<LLookupField> _lookupFields;

  bool _modified = false;

  void setCacheAction(LSqlRecord &rec, LSqlRecord::CacheAction action);
  bool submitRecord(LSqlRecord &rec);
  bool reloadRow(int row);
  bool isNull(const QModelIndex &index);
  QVariant sqlValue(QVariant val, QMetaType::Type type);
  //Get next sequence value
  qlonglong nextSequenceNumber();
  bool returningInsertMode();
  int _insertedCount = 0;
  bool _autoIncrementID;
protected:
  CacheMap _recMap;
  QList<qlonglong> _recIndex;

  void clearData();
  QSqlRecord primaryValues(QSqlRecord rec) const;
  qlonglong primaryKey(int row, int part = 0);
  QString primaryKeyName(int part = 0);
  int primaryKeyCount();
  QSqlDatabase _db;
  QSqlQuery _query;

  virtual QString selectAllSql();
  virtual bool selectRowInTable(QSqlRecord &values);
  virtual bool updateRowInTable(const QSqlRecord &values);
  virtual bool insertRowInTable(const QSqlRecord &values);
  virtual bool deleteRowInTable(const QSqlRecord &values);
};

class LLookupField : public QSqlField
{
public:
  LSqlTableModel* lookupModel;
  QString lookupField;
  QString keyField;
  QVariant data(qlonglong key);
};

#endif // LSQLTABLEMODEL_H
