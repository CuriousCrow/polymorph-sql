#include "qdbstructuremodel.h"
#include <QIcon>
#include <QDebug>
#include <QBrush>
#include <QPixmap>

QDBStructureModel::QDBStructureModel(QObject *parent, QSqlDatabase db) : LSqlTreeModel(parent, db)
{

}

QDBStructureModel::~QDBStructureModel()
{

}

void QDBStructureModel::addItem(qlonglong id, QString name, int type, qlonglong parentId)
{
  LSqlRecord rec(patternRec());
  rec.setValue("ID", id);
  rec.setValue("NAME", name);
  rec.setValue("PARENT_ID", parentId);
  rec.setValue("TYPE", type);
  addRecord(rec);
}

QVariant QDBStructureModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  LSqlRecord rec = recById(index.internalId());
  int type = rec.value("TYPE").toInt();

  if (role == Qt::DecorationRole){
    if (type == 0)
      return QIcon(":/icons/database.png");
    else if (type == 1)
      return QIcon(":/icons/table.png");
    else if (type == 2)
      return QIcon(":/icons/column.png");
    else
      return QVariant();
  }
  return LSqlTreeModel::data(index, role);
}
