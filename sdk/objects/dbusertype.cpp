#include "dbusertype.h"

DBUserType::DBUserType() : DBObjectItem(nullptr)
{

}


bool DBUserType::reloadChildren()
{
  return true;
}

int DBUserType::type() const
{
  return DBObjectItem::UserType;
}
