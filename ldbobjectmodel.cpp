#include "ldbobjectmodel.h"
#include <QDebug>
#include "dbms/appconst.h"

//Поиск имени таблицы по алиасу
//(FROM|JOIN)\s+([^\s]+)\s+t


LDBObjectModel::LDBObjectModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void LDBObjectModel::reload(QStringList keywords, QString connName)
{
  qDebug() << connName;
  emit beginResetModel();
  _dataList.clear();
  foreach (QString keyword, keywords) {
    _dataList.append(DbObj(keyword, F_KEYWORD));
  }
  QSqlDatabase db = QSqlDatabase::database(connName);
  QString sql;
  if (db.driverName() == DRIVER_PSQL) {
    sql = "select table_name, 'table' FROM information_schema.tables "
          "WHERE table_schema = 'public' AND table_type = 'BASE TABLE' "
          "UNION ALL "
          "SELECT table_name, 'view' FROM information_schema.views "
          "WHERE table_schema = 'public' "
          "UNION ALL "
          "SELECT sequence_name, 'sequence' FROM information_schema.sequences "
          "UNION ALL "
          "SELECT routine_name, 'procedure' FROM information_schema.routines "
          "WHERE specific_schema NOT IN ('pg_catalog', 'information_schema') "
          "AND type_udt_name != 'trigger'";
  }
  else if (db.driverName() == DRIVER_MYSQL) {
    sql = "SELECT table_name, 'table' FROM information_schema.tables "
          "WHERE table_schema = 'test' AND table_type = 'BASE TABLE' "
          "UNION ALL "
          "SELECT table_name, 'view' FROM information_schema.views "
          "UNION ALL "
          "SELECT routine_name, 'procedure' FROM information_schema.routines "
          "WHERE ROUTINE_TYPE='PROCEDURE' ";
  }
  else if (db.driverName() == DRIVER_FIREBIRD) {
    sql = "select trim(rdb$relation_name), 'table' from rdb$relations where rdb$relation_type=0 and (rdb$system_flag is null or rdb$system_flag = 0) "
          "union all "
          "select trim(rdb$relation_name) name, 'view' from rdb$relations where rdb$relation_type=1 "
          "union all "
          "select trim(rdb$generator_name) name, 'sequence' from rdb$generators where rdb$system_flag = 0 "
          "union all "
          "select trim(rdb$procedure_name) name, 'procedure' from rdb$procedures";
  }
  else if (db.driverName() == DRIVER_SQLITE) {
    sql = "SELECT name, type FROM sqlite_master";
  }
  if (!sql.isEmpty()) {
    QSqlQuery query(db);
    query.exec(sql);
    while (query.next()) {
      _dataList.append(DbObj(query.value(0).toString(), query.value(1).toString()));
    }
  }
  emit endResetModel();
}

DbObj LDBObjectModel::findByName(QString objName)
{
  foreach(DbObj obj, _dataList) {
    if (obj.name == objName)
      return obj;
  }
  return DbObj();
}

int LDBObjectModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  return _dataList.count();
}

int LDBObjectModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  return 2;
}

QVariant LDBObjectModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    if (index.column() == 0)
      return _dataList.at(index.row()).name;
    else
      return _dataList.at(index.row()).type;
  }
  return QVariant();
}

DbObj::DbObj(QString name, QString type)
{
  this->name = name;
  this->type = type;
}
