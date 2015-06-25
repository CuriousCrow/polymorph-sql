#ifndef LSQLTREEMODEL_H
#define LSQLTREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlIndex>
#include <QSqlError>

#define PRIMARY_KEY_FIELD "ID"
#define PARENT_ID_FIELD "PARENT_ID"

class LSqlTreeRecord : public QSqlRecord
{
public:
  LSqlTreeRecord();
  LSqlTreeRecord(const QSqlRecord& rec);
  ~LSqlTreeRecord();
  void copyValues(const QSqlRecord& rec);
  void addChild(long childId);
  void removeChild(long childId);
  qlonglong childByIndex(int index);
  int childIndex(qlonglong childId);
  int childCount();
  qlonglong id(){ return value(PRIMARY_KEY_FIELD).toLongLong(); }
private:
  QList<qlonglong> _childIdList;
};

class LSqlTreeModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit LSqlTreeModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
  ~LSqlTreeModel();
private:
  QSqlDatabase _db;
  QSqlQuery _query;
  QMap<qlonglong, LSqlTreeRecord> _recMap;
  QList<qlonglong> _rootRecList;
  QString _tableName;
  QSqlIndex _primaryIndex;
  QSqlRecord _patternRec;
  QString _parentField = PARENT_ID_FIELD;
  qlonglong itemParentId(LSqlTreeRecord rec) const;
  void clear();
public:
  void addRecord(LSqlTreeRecord rec);
  bool setTable(QString tableName);  
  virtual bool select();
  virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
  QModelIndex indexById(qlonglong id);
  virtual QModelIndex parent(const QModelIndex &child) const;
  virtual int rowCount(const QModelIndex &parent) const;
  virtual int columnCount(const QModelIndex &parent) const;
  virtual QVariant data(const QModelIndex &index, int role) const;  
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
  virtual bool removeRows(int row, int count, const QModelIndex &parent);
  bool removeChildren(qlonglong parentId);
  bool removeAllChildren(const QModelIndex &parent);
  void setParentField(QString name);
  LSqlTreeRecord patternRec() const;
  int fieldIndex(QString fieldName) const;
  LSqlTreeRecord recById(qlonglong id) const;
  //TODO: Should be static method
  QVariant execQuery(const QString &sql, QString resColumn);
  //Wrapper for all sql-queries (for debugging)
  bool execQuery(const QString &sql);        
};

#endif // LSQLTREEMODEL_H
