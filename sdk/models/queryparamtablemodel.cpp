#include "queryparamtablemodel.h"



QueryParamTableModel::QueryParamTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void QueryParamTableModel::setParams(QVariantMap params)
{
    beginResetModel();
    _params = params;
    endResetModel();
}

QVariantMap QueryParamTableModel::params() const
{
    return _params;
}

void QueryParamTableModel::updateParams(QVariantMap params)
{
    beginResetModel();
    foreach(QString key, params.keys()) {
      if (!_params.contains(key)) {
        _params.insert(key, params.value(key));
      }
    }
    endResetModel();
}

void QueryParamTableModel::deleteParam(QString name)
{
    int index = rowByName(name);
    if (index < 0)
        return;
    beginRemoveRows(QModelIndex(), index, index);
    _params.remove(name);
    endRemoveRows();
}

void QueryParamTableModel::deleteParam(int row)
{
    QString name = nameByRow(row);
    beginRemoveRows(QModelIndex(), row, row);
    _params.remove(name);
    endRemoveRows();
}

void QueryParamTableModel::addParam(QString name, QVariant value)
{
    if (_params.contains(name))
        return;
    _params.insert(name, value);
    int index = rowByName(name);
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}

void QueryParamTableModel::clear()
{
    setParams(QVariantMap());
}

int QueryParamTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _params.count();
}

int QueryParamTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant QueryParamTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString name = nameByRow(index.row());
        switch(index.column()) {
        case 0:
            return name;
        case 1:
            return _params.value(name);
        }
    }
    return QVariant();
}

Qt::ItemFlags QueryParamTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool QueryParamTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::EditRole) {
        QString name = nameByRow(index.row());
        _params.insert(name, value);
        return true;
    }
    return false;
}

QVariant QueryParamTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Parameter");
        case 1:
            return tr("Value");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QString QueryParamTableModel::nameByRow(int row) const
{
    QStringList keys = _params.keys();
    return keys.value(row);
}

int QueryParamTableModel::rowByName(const QString &name) const
{
    const QStringList keys = _params.keys();
    return keys.indexOf(name);
}










