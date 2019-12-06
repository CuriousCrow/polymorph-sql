#include "postgresuniqueconstraint.h"


PostgresUniqueConstraint::PostgresUniqueConstraint(QString caption, QObject *parent)
  : DBUniqueConstraint(caption, parent)
{

}


bool PostgresUniqueConstraint::refresh()
{
}