#include "firebirdtable.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"


FirebirdTable::FirebirdTable()
  : DBTableItem()
{
  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
  registerDependantObject(_constraintsModel);
}

FirebirdTable::~FirebirdTable()
{
}

void FirebirdTable::reloadColumnsModel()
{
  //New but not inserted table
  if (connectionName().isEmpty())
    return;
  _columnsModel->clear();
  QStringList primaryColumns;

  QString sql =
      "select trim(i.RDB$FIELD_NAME) "
      "from RDB$RELATION_CONSTRAINTS rc "
      "left join RDB$INDEX_SEGMENTS i on rc.RDB$INDEX_NAME = i.RDB$INDEX_NAME "
      "where rc.RDB$CONSTRAINT_TYPE = 'PRIMARY KEY' and rc.RDB$RELATION_NAME = '#caption#'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery query = SqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    primaryColumns.append(query.value(0).toString());
  }

  sql = "SELECT r.RDB$FIELD_NAME AS ccaption, r.RDB$DESCRIPTION AS cdescription, r.RDB$DEFAULT_VALUE AS cdefault, r.RDB$NULL_FLAG AS cnot_null, "
                "f.RDB$CHARACTER_LENGTH AS clength, f.RDB$FIELD_PRECISION AS cprecision, f.RDB$FIELD_SCALE AS cscale, "
                "CASE f.RDB$FIELD_TYPE "
                "WHEN 261 THEN 'BLOB' "
                "WHEN 14 THEN 'CHAR' "
                "WHEN 40 THEN 'CSTRING' "
                "WHEN 11 THEN 'D_FLOAT' "
                "WHEN 27 THEN 'DOUBLE' "
                "WHEN 10 THEN 'FLOAT' "
                "WHEN 16 THEN 'BIGINT' "
                "WHEN 8 THEN 'INTEGER' "
                "WHEN 9 THEN 'QUAD' "
                "WHEN 7 THEN 'SMALLINT' "
                "WHEN 12 THEN 'DATE' "
                "WHEN 13 THEN 'TIME' "
                "WHEN 35 THEN 'TIMESTAMP' "
                "WHEN 37 THEN 'VARCHAR' "
                "ELSE 'UNKNOWN' END AS ctype, "
                "iif(POSITION('RDB$' IN f.rdb$field_name)>0, 0, 1) AS ctypekind "
                "FROM RDB$RELATION_FIELDS r "
                "LEFT JOIN RDB$FIELDS f ON r.RDB$FIELD_SOURCE = f.RDB$FIELD_NAME "
                "WHERE r.RDB$RELATION_NAME='#caption#' ORDER BY r.RDB$FIELD_POSITION";
  preparedSql = fillSqlPatternWithFields(sql);
  query = SqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    QString name = query.value("ccaption").toString().trimmed();
    SqlColumn col(name, query.value("ctype").toString().trimmed());
    col.setDefaultValue(query.value("cdefault"));
    col.setIsPrimary(primaryColumns.contains(name));
    col.setLength(query.value("clength").toInt());
    col.setPrecision(query.value("cprecision").toInt());
    col.setNotNull(query.value("cnot_null").toBool());
    qDebug() << name << query.value("ctypekind").toInt();
    col.setTypeKind((TypeKind)query.value("ctypekind").toInt());
    _columnsModel->addSqlColumn(col, true);
  }
}

QString FirebirdTable::createTableQuery(QString table) const
{
  QString createPattern = "CREATE TABLE %1 (%2);";
  QStringList pkColList;
  QStringList colDefList;
  for(int i=0; i<_columnsModel->rowCount(); i++) {
    SqlColumn col = _columnsModel->columnByIndex(i);
    if (col.isPrimary())
      pkColList.append(col.name());
    QString colDef = columnDef(col);
    colDefList.append(colDef);
  }
  if (!pkColList.isEmpty()) {
    QString pkTemplate = "CONSTRAINT pk_#caption.new# PRIMARY KEY (%1)";
    colDefList.append(fillSqlPatternWithFields(pkTemplate).arg(pkColList.join(",")));
  }
  QString preparedSql = createPattern.arg(table, colDefList.join(", "));
  return preparedSql;
}

QString FirebirdTable::columnDef(const SqlColumn &col) const
{
  bool isDomain = col.typeKind() == TypeKind::Custom;
  QString colType = isDomain ? "\"" + col.type() + "\"" : col.type();
  QString colDef = col.name() + " " + colType;
  if (col.length() > 0)
    colDef.append("(" + QString::number(col.length()) + ")");
  if (col.notNull())
    colDef = colDef.append(" NOT NULL");
  if (!col.defaultValue().isNull())
    colDef = colDef.append(" DEFAULT ").append(col.defaultValue().toString());
  return colDef;
}

QString FirebirdTable::typeDef(const SqlColumn &col) const
{
  QString strType = col.type();
  if (col.length() > 0)
    strType = QString("%1(%2)").arg(strType).arg(col.length());
  return strType;
}

ActionResult FirebirdTable::insertMe()
{
  QString sql = toDDL();
  setFieldValue(F_CAPTION, caption().toUpper());
  return execSql(sql, connectionName());
}

ActionResult FirebirdTable::updateMe()
{
  qDebug() << "QDBPostgreqlTableItem::updateMe()";
  ActionResult res;

  //Renaming not supported in Firebird
  if (fieldModified(F_CAPTION)) {
    qDebug() << "Rename table";
    return ActionResult(RES_BASE_ERROR, tr("Renaming is not supported"));
  }

  res = DBTableItem::updateMe();
  if (res.isSuccess())
    return RES_OK_CODE;
  else
    res = ActionResult(RES_OK_CODE);

  QHash<SqlColumn, SqlColumn> changes = _columnsModel->columnChanges();
  qDebug() << "Changes size:" << changes.count();
  QList<SqlColumn> keys = changes.keys();
  foreach (SqlColumn fromCol, keys) {
    SqlColumn toCol = changes[fromCol];
    //    qDebug() << "Changes:" << fromCol << toCol;
    if (fromCol.type() == NoType) {
      //Add column
      qDebug() << "Add col:" << toCol;
      QString sql = "ALTER TABLE \"#caption.new#\" ADD %1";
      QString colDef = columnDef(toCol);
      QString preparedSql = fillSqlPatternWithFields(sql).arg(colDef);
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
    else if (toCol.type() == NoType) {
      //Drop column
      qDebug() << "Drop col:" << fromCol;
      QString sql = "ALTER TABLE \"#caption.new#\" DROP %1";
      QString preparedSql = fillSqlPatternWithFields(sql).arg(fromCol.name());
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
    else {
      //Change column
      qDebug() << "Col modify:" << fromCol << "to" << toCol;
      QStringList difs;
      QString pattern;

      //NOT NULL
      if (fromCol.notNull() != toCol.notNull()) {
        pattern = "UPDATE RDB$RELATION_FIELDS SET RDB$NULL_FLAG = %1 "
                  "WHERE RDB$FIELD_NAME = '%2' AND RDB$RELATION_NAME = '%3'";
        QString preparedSql = pattern.arg((toCol.notNull() ? "1" : "NULL"), toCol.name(), caption());
        res = execSql(preparedSql, connectionName());
        if (!res.isSuccess())
          return res;
      }
      //COLUMN TYPE
      if (fromCol.type() != toCol.type() || fromCol.length() != toCol.length()) {
        pattern = "ALTER COLUMN %1 TYPE %2";
        difs.append(pattern.arg(toCol.name(), typeDef(toCol)));
      }
      //DEFAULT VALUE
      if (fromCol.defaultValue() != toCol.defaultValue()) {
        if (toCol.defaultValue().toString().isEmpty())
          pattern = "ALTER COLUMN %1 DROP DEFAULT %2";
        else {
          pattern = "ALTER COLUMN %1 SET DEFAULT %2";
        }
        difs.append(pattern.arg(toCol.name(), toCol.defaultValue().toString()));
      }
//    Since FIREBIRD3
//      if (fromCol.notNull() != toCol.notNull()) {
//        pattern = "ALTER COLUMN %1 ";
//        pattern.append(toCol.notNull() ? "SET NOT NULL" : "DROP NOT NULL");
//        difs.append(pattern.arg(toCol.name()));
//      }
      //RENAME COLUMN
      if (fromCol.name() != toCol.name()) {
        pattern = "ALTER COLUMN \"%1\" TO \"%2\"";
        difs.append(pattern.arg(fromCol.name(), toCol.name()));
      }
      if (difs.isEmpty()) {
        qWarning() << "Column unchanged case! Ignore column.";
        continue;
      }

      QString sql = "ALTER TABLE \"#caption.new#\" " + difs.join(",\n");
      QString preparedSql = fillSqlPatternWithFields(sql);
      res = execSql(preparedSql, connectionName());
      if (!res.isSuccess())
        return res;
    }
  }
  return res;
}

QString FirebirdTable::toDDL() const
{
  return createTableQuery(identifier().toUpper());
}

void FirebirdTable::reloadConstraintsModel()
{
  //New table (not yet commited)
  if (connectionName().isEmpty())
    return;
  _constraintsModel->clear();
  QString sql =
      "select trim(RDB$CONSTRAINT_NAME) \"name\", trim(RDB$CONSTRAINT_TYPE) \"type\"\n"
      "from RDB$RELATION_CONSTRAINTS\n"
      "where RDB$RELATION_NAME = '#caption#' and RDB$CONSTRAINT_TYPE <> 'NOT NULL'";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery query = SqlQueryHelper::execSql(preparedSql, connectionName());
  int fakeId = 1;
  while (query.next()) {
    QVariantMap item;
    item.insert(F_ID, fakeId++);
    item.insert(F_NAME, query.value(F_NAME));
    item.insert(F_TYPE, query.value(F_TYPE));
    _constraintsModel->addRow(item);
  }
}
