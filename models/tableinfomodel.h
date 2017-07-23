#ifndef TABLEINFOMODEL_H
#define TABLEINFOMODEL_H

#include <QObject>
#include <QAbstractTableModel>

enum ColumnType {
  NoType     = 0x0,
  BigInt     = 0x1,
  Integer    = 0x2,
  SmallInt   = 0x4,
  Varchar    = 0x8,
  Numeric    = 0x10,
  Char       = 0x20,
  Date       = 0x40,
  Time       = 0x80,
  Timestamp  = 0x100,
  Boolean    = 0x200,
  Blob       = 0x400,
  AllTypes   = 0xFFF
};

Q_DECLARE_FLAGS(ColumnTypes, ColumnType)
Q_DECLARE_OPERATORS_FOR_FLAGS(ColumnTypes)

class SqlColumn
{
public:
  SqlColumn();
  SqlColumn(QString name, ColumnType type);
  SqlColumn(const SqlColumn &other);
  QString name() const;
  void setName(const QString &name);

  QString oldName();

  ColumnType type() const;
  void setType(const ColumnType &type);

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

  bool operator ==(const SqlColumn &other);

private:
  QString _name;
  QString _oldName;
  ColumnType _type;
  int _length;
  int _precision;
  bool _notNull;
  bool _isPrimary;
  QVariant _defaultValue;
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

class TableInfoModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  enum EditType {
      NoChanges = 0,
      ModifyTable = 1,
      CreateTable = 2,
      DropTable = 3
  };

  TableInfoModel(QObject* parent = 0);
  virtual ColumnTypes supportedColumnTypes() = 0;
  virtual QString columnTypeCaption(const ColumnType type) const = 0;
  void addSqlColumn(SqlColumn col, bool init = false);
  SqlColumn columnByIndex(int idx);
  int rowByName(const QString name);
  QHash<SqlColumn, SqlColumn> columnChanges();
  EditType editType();
  void revertAll();
  void clear();
public:
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
private:
  QList<QString> _idxList;
  QHash<QString, SqlColumn> _dataHash;
  QHash<QString, SqlColumn> _changes;
};

class SqliteTableInfoModel : public TableInfoModel
{
  Q_OBJECT
public:
  SqliteTableInfoModel(QObject* parent = 0);
public:
  virtual ColumnTypes supportedColumnTypes();
  virtual QString columnTypeCaption(const ColumnType type) const;
};


#endif // TABLEINFOMODEL_H
