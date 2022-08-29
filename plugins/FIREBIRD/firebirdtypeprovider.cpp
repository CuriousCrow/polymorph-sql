#include "firebirdtypeprovider.h"
#include "objects/appconst.h"
#include "objects/foldertreeitem.h"

FirebirdTypeProvider::FirebirdTypeProvider() : BaseTypeProvider()
{
}

void FirebirdTypeProvider::reload()
{
  BaseTypeProvider::reload();

  DBObjectItem* domainFolder = _ds->itemByFolderAndName(_itemObj, FOLDER_USER_TYPE);
  foreach(QObject* obj, domainFolder->children()) {
    DBObjectItem* item = static_cast<DBObjectItem*>(obj);
    _types.append(new StringDBType(item->caption(), item->caption()));
  }
}


