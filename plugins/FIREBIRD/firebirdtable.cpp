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
  QString sql = "SELECT r.RDB$FIELD_NAME AS ccaption, r.RDB$DESCRIPTION AS cdescription, r.RDB$DEFAULT_VALUE AS cdefault, r.RDB$NULL_FLAG AS cnot_null, "
                "f.RDB$FIELD_LENGTH AS clength, f.RDB$FIELD_PRECISION AS cprecision, f.RDB$FIELD_SCALE AS cscale, "
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
                "ELSE 'UNKNOWN' END AS ctype "
                "FROM RDB$RELATION_FIELDS r "
                "LEFT JOIN RDB$FIELDS f ON r.RDB$FIELD_SOURCE = f.RDB$FIELD_NAME "
                "WHERE r.RDB$RELATION_NAME='#caption#' ORDER BY r.RDB$FIELD_POSITION;";
  QString preparedSql = fillSqlPatternWithFields(sql);
  QSqlQuery query = SqlQueryHelper::execSql(preparedSql, connectionName());
  while (query.next()) {
    SqlColumn col(query.value("ccaption").toString().trimmed(),
                  colTypeFromString(query.value("ctype").toString().trimmed()));
    col.setDefaultValue(query.value("cdefault"));
    col.setIsPrimary(false);
    col.setLength(query.value("clength").toInt());
    col.setPrecision(query.value("cprecision").toInt());
    col.setNotNull(query.value("cnot_null").toBool());
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
  QString colDef = col.name() + " " + _columnsModel->columnTypeCaption(col.type());
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
  QString strType = _columnsModel->columnTypeCaption(col.type());
  if (col.length() > 0)
    strType = QString("%1(%2)").arg(strType).arg(col.length());
  return strType;
}

ActionResult FirebirdTable::insertMe()
{
  QString sql = createTableQuery(identifier().toUpper());
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
      if (fromCol.type() != toCol.type() || fromCol.length() != toCol.length()) {
        pattern = "ALTER COLUMN %1 TYPE %2";
        difs.append(pattern.arg(toCol.name(), typeDef(toCol)));
      }
      if (fromCol.defaultValue() != toCol.defaultValue()) {
        if (toCol.defaultValue().toString().isEmpty())
          pattern = "ALTER COLUMN %1 DROP DEFAULT %2";
        else {
          pattern = "ALTER COLUMN %1 SET DEFAULT %2";
        }
        difs.append(pattern.arg(toCol.name(), toCol.defaultValue().toString()));
      }
      if (fromCol.notNull() != toCol.notNull()) {
        pattern = "ALTER COLUMN %1 ";
        pattern.append(toCol.notNull() ? "SET NOT NULL" : "DROP NOT NULL");
        difs.append(pattern.arg(toCol.name()));
      }
      if (fromCol.name() != toCol.name()) {
        pattern = "RENAME COLUMN \"%1\" TO \"%2\"";
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


