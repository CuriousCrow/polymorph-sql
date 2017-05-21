#include "lcachedtablemodel.h"


LCachedTableModel::LCachedTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

void LCachedTableModel::registerField(QString field)
{
    _fieldNames.append(field);
    _sampleRec.setValue(field, QVariant());
}

void LCachedTableModel::addRec(LVariantRec rec)
{
    QString idxField = _fieldNames.at(_idColIdx);
    QVariant id = rec.value(idxField);

    //Если поле идентификатора не заполнено, генерируем значение
    if (!id.isValid()) {
        id = _defIdGen++;
        rec.setValue(idxField, id);
    }
    beginInsertRows(QModelIndex(), _idList.count(), _idList.count());
    _idList.append(id);
    _rows.insert(id, rec);
    _changes.insert(id, rec);
    endInsertRows();
}

void LCachedTableModel::setIdField(QString field)
{
    _idColIdx = _fieldNames.indexOf(field);
}

QVariant LCachedTableModel::idByRow(int row) const
{
    return _idList.at(row);
}

QString LCachedTableModel::fieldByIndex(int col) const
{
    return _fieldNames.at(col);
}


int LCachedTableModel::rowCount(const QModelIndex &parent) const
{
    return _idList.count();
}

int LCachedTableModel::columnCount(const QModelIndex &parent) const
{
    return _fieldNames.count();
}

QVariant LCachedTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    QVariant id = idByRow(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:

      return _changes.contains(id) ? _changes.value(id).value(fieldByIndex(index.column()))
                                   : _rows.value(id).value(fieldByIndex(index.column()));
    default:
        break;
    }
    return QVariant();
}

bool LCachedTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    QVariant id = idByRow(index.row());
    switch (role) {
    case Qt::EditRole:
        if (!_changes.contains(id))
            _changes.insert(id, LVariantRec(_rows.value(id)));
        _changes[id].setValue(fieldByIndex(index.column()), value);
        break;
    default:
        break;
    }
    return false;
}

QVariant LCachedTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
      if (role == Qt::DisplayRole) {
          return _fieldNames.at(section);
      }
    }
    return QVariant();
}

Qt::ItemFlags LCachedTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void LCachedTableModel::revert()
{
    beginResetModel();
    foreach (QVariant id, _changes.keys()) {
        //Удаленная строка
        if (!_idList.contains(id)) {
            //Возвращаем в индекс
            _idList.append(id);
        }
        //Добавленная строка
        if (!_rows.contains(id)) {
            _idList.removeOne(id);
        }
    }
    _changes.clear();
    endResetModel();
}

bool LCachedTableModel::submitAll()
{
    foreach (QVariant id, _changes.keys()) {
        _rows.insert(id, _changes.value(id));
        _changes.remove(id);
    }
}

bool LCachedTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid() || count > 1)
      return false;
    QString idxField = _fieldNames.at(_idColIdx);
    QVariant id = _defIdGen++;
    LVariantRec newRec = LVariantRec(_sampleRec);
    newRec.setValue(idxField, QVariant(id));
    beginInsertRows(parent, row, row);
    _idList.insert(row, id);
    _changes.insert(id, newRec);
    endInsertRows();
    return true;
}

bool LCachedTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    QString idxField = _fieldNames.at(_idColIdx);
    QVariant id = _idList.at(row);
    LVariantRec rec;
    rec.setValue(idxField, id);
    beginRemoveRows(QModelIndex(), row, row);
    _changes.insert(id, rec);
    _idList.removeAt(row);
    endRemoveRows();
}

LVariantRec::LVariantRec()
{
}

LVariantRec::LVariantRec(const LVariantRec &obj)
{
    _dataMap = obj._dataMap;
}

QVariant LVariantRec::value(QString field) const
{
    return _dataMap.value(field);
}

void LVariantRec::setValue(QString field, QVariant val)
{
    _dataMap.insert(field, val);
}
