#include "firebirdtable.h"
#include "utils/sqlqueryhelper.h"
#include "objects/appconst.h"


FirebirdTable::FirebirdTable()
  : DBTableItem()
{
  _constraintsModel = new VariantMapTableModel();
  _constraintsModel->registerColumn(F_TYPE, tr("Type"));
  _constraintsModel->registerColumn(F_NAME, tr("Name"));
}

FirebirdTable::~FirebirdTable()
{
  delete _columnsModel;
  delete _constraintsModel;
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