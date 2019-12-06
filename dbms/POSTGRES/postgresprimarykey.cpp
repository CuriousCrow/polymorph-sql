#include "postgresprimarykey.h"

PostgresPrimaryKey::PostgresPrimaryKey(QString caption, QObject *parent)
  : DBPrimaryKey(caption, parent)
{

}

bool PostgresPrimaryKey::refresh()
{
  return DBPrimaryKey::refresh();
}
