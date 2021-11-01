#include "firebirdsequence.h"
#include "objects/appconst.h"

FirebirdSequence::FirebirdSequence() : DBSequenceItem()
{

}

QString FirebirdSequence::toDDL() const
{
    QString sqlPattern = "create sequence \"%1\"";
    return sqlPattern.arg(fieldValue(F_CAPTION).toString());
}

ActionResult FirebirdSequence::insertMe()
{
    QString sql = toDDL();
    return execSql(sql, connectionName());
}

ActionResult FirebirdSequence::updateMe()
{
    QString sqlPattern = "ALTER SEQUENCE \"%1\" RESTART WITH %2";
    return execSql(sqlPattern.arg(fieldValue(F_CAPTION).toString(), fieldValue(F_CURRENT_VALUE).toInt()),
                   connectionName());
}
