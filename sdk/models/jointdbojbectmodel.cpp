#include "jointdbojbectmodel.h"


JointDBOjbectModel::JointDBOjbectModel(QObject *parent)
  : QAbstractTableModel(parent)
{

}

void JointDBOjbectModel::registerColumn(QString colName)
{
  beginInsertColumns(QModelIndex(), _columns.count(), _columns.count());
  _columns.append(colName);
  endInsertColumns();
}

void JointDBOjbectModel::addModel(QString name, LDBObjectTableModel *model)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount() + model->rowCount());
  _modelNames.append(name);
  _models.append(model);
  endInsertRows();
}

void JointDBOjbectModel::clear()
{
  beginResetModel();
  _modelNames.clear();
  _models.clear();
  endResetModel();
}

QVariantMap JointDBOjbectModel::rowDataByName(QString name, QString modelName)
{
  foreach(QString itemName, _modelNames) {
    if (!modelName.isEmpty() && itemName != modelName)
      continue;
    LDBObjectTableModel* model = _models.at(_modelNames.indexOf(itemName));
    if (model->contains(name)) {
      return model->rowByName(name);
    }
  }
  return QVariantMap();
}


int JointDBOjbectModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)

  int rows = 0;
  foreach(LDBObjectTableModel* model, _models) {
    rows += model->rowCount();
  }
  return rows;
}

int JointDBOjbectModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _columns.count();
}

QVariant JointDBOjbectModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole || role == Qt::EditRole){
    //Just in case
    if (_models.isEmpty())
      return QVariant();
    int rest = index.row();
    foreach(LDBObjectTableModel* model, _models) {
      if (model->rowCount() > rest) {
        return model->data(model->index(rest, index.column()), role);
      }
      rest -= model->rowCount();
    }
    return QVariant();
  }
  return QVariant();
}
