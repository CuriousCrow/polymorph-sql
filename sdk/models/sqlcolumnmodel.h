#ifndef SQLCOLUMNMODEL_H
#define SQLCOLUMNMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include "core/dependencycontainer.h"
#include "core/lknowledgebase.h"
#include "objects/typeprovider.h"

#define NoType ""
#define COL_IDX_PK 0
#define COL_IDX_NAME 1
#define COL_IDX_TYPE 2
#define COL_IDX_LENGTH 3
#define COL_IDX_PRECISION 4
#define COL_IDX_NOTNULL 5
#define COL_IDX_DEFAULT 6
#define COL_IDX_AUTOINCREMENT 7

enum TypeKind {
  Standard = 0,
  Custom = 1
};

class SqlColumn
{
public:
  SqlColumn();
  SqlColumn(QString name, QString type);

  QString name() const;
  void setName(const QString &name);

  QString type() const;
  void setType(const QString &type);

  int length() const;
  void setLength(int length);

  int precision() const;
  void setPrecision(int precision);

  bool notNull() const;
  void setNotNull(bool notNull);

  bool isPrimary() const;
  void setIsPrimary(bool isPrimary);

  QVariant defaultValue() const;
  void setDefaultValue(const QVariant &defaultValue);

  bool autoIncrement() const;
  void setAutoIncrement(bool autoIncrement);

  TypeKind typeKind() const;
  void setTypeKind(const TypeKind kind);

  QVariant valueByIndex(int idx);

  bool operator ==(const SqlColumn &other);

private:
  QVariantHash _colData;
};

inline uint qHash(const SqlColumn &key) {
  return qHash(key.name());
}

inline bool operator ==(const SqlColumn &col1, const SqlColumn &col2) {
  return (col1.name() == col2.name()) && (col1.type() == col2.type())
      && (col1.length() == col2.length()) && (col1.isPrimary() == col2.isPrimary())
      && (col1.notNull() == col2.notNull()) && (col1.defaultValue() == col2.defaultValue());
}

QDebug operator<<(QDebug dbg, const SqlColumn &column);

class SqlColumnModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  enum EditType {
    NoChanges = 0,
    ModifyTable = 1,
    CreateTable = 2,
    DropTable = 3
  };
  Q_INVOKABLE SqlColumnModel(QObject *parent = Q_NULLPTR);

  INJECT(LKnowledgeBase*, kb)

  void setTypeProvider(TypeProvider* provider);
  void addSqlColumn(SqlColumn col, bool init = false);
  SqlColumn columnByIndex(int idx);
  int rowByName(const QString name);
  QHash<SqlColumn, SqlColumn> columnChanges();
  QHash<QString, QString> permanentColNames();
  EditType editType();
  bool hasOneColumnPK();
  bool isModified();
  void clear();

  // QAbstractItemModel interface
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
  TypeProvider* _typeProvider;
  qlonglong getNextId();
private slots:
  void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
private:
  qlonglong _idGen = 1;
  QList<qlonglong> _idxList;
  QHash<qlonglong, SqlColumn> _dataHash;
  QHash<qlonglong, SqlColumn> _changes;
  QColor _modifiedColor = Qt::green;
  QColor _errorColor = Qt::red;
  bool hasLength(int row) const;
};

#endif // SQLCOLUMNMODEL_H
