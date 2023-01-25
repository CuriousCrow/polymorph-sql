#include "firebirdtypeprovider.h"
#include "objects/appconst.h"
#include "objects/foldertreeitem.h"

FirebirdDomainType::FirebirdDomainType(QString name, QString title) : BaseDBType(name, title)
{
}

bool FirebirdDomainType::isUserType() const
{
  return true;
}

QString FirebirdDomainType::valueToSql(const QVariant &value)
{
  return value.toString();
}


FirebirdTypeProvider::FirebirdTypeProvider() : BaseTypeProvider()
{
}

void FirebirdTypeProvider::reload()
{
  BaseTypeProvider::reload();

  DBObjectItem* domainFolder = _ds->itemByFolderAndName(_itemObj, FOLDER_USER_TYPE);
  foreach(QObject* obj, domainFolder->children()) {
    DBObjectItem* item = static_cast<DBObjectItem*>(obj);
    _types.append(new FirebirdDomainType(item->caption(), item->caption()));
  }
}


