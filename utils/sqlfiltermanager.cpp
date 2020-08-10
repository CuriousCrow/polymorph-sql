#include "sqlfiltermanager.h"
#include <QDebug>

SqlFilterManager::SqlFilterManager(QObject* parent) : QAbstractListModel(parent)
{
}

void SqlFilterManager::addEqualFilter(QString field, QVariant value, bool exclude, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  SqlFilter filter(joint, field, exclude ? WhereOperator::NotEquals : WhereOperator::Equals, values);
  addFilter(filter);
}

void SqlFilterManager::addEqualFilter(QString field, QVariantList values, bool exclude, WhereJoint joint)
{
  SqlFilter filter(joint, field, exclude ? WhereOperator::NotEquals : WhereOperator::Equals, values);
  addFilter(filter);
}

void SqlFilterManager::addNullFilter(QString field, bool exclude, WhereJoint joint)
{
  SqlFilter filter(joint, field, exclude ? WhereOperator::IsNotNull : WhereOperator::IsNull, QVariantList());
  addFilter(filter);
}

void SqlFilterManager::addMoreThanFilter(QString field, QVariant value, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  SqlFilter filter(joint, field, WhereOperator::MoreThan, values);
  addFilter(filter);
}

void SqlFilterManager::addLessThanFilter(QString field, QVariant value, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  SqlFilter filter(joint, field, WhereOperator::LessThan, values);
  addFilter(filter);
}

void SqlFilterManager::addBetweenFilter(QString field, QVariant fromValue, QVariant toValue, WhereJoint joint)
{
  QVariantList values;
  values.append(fromValue);
  values.append(toValue);
  SqlFilter filter(joint, field, WhereOperator::Between, values);
  addFilter(filter);
}

void SqlFilterManager::removeFilter(int idx)
{
  beginRemoveRows(QModelIndex(), idx, idx);
  _filters.removeAt(idx);
  endRemoveRows();
}

void SqlFilterManager::clear()
{
  beginResetModel();
  _filters.clear();
  endResetModel();
}

QString SqlFilterManager::whereClause()
{
  if (_filters.isEmpty())
    return "";
  QString result;
  foreach(SqlFilter filter, _filters) {
    if (!result.isEmpty()) {
      switch (filter.joint()) {
      case WhereJoint::And:
        result.append(" ").append("AND").append(" ");
        break;
      case WhereJoint::Or:
        result.append(" ").append("OR").append(" ");
        break;
      case WhereJoint::None:
        break;
      }
    }
    result.append(filter.toString());
  }
  return result.prepend(" where ");
}

void SqlFilterManager::addFilter(SqlFilter &filter)
{
  beginInsertRows(QModelIndex(), _filters.count(), _filters.count());
  qDebug() << "Add filter:" << _filters.count();
  _filters.append(filter);
  endInsertRows();
}

SqlFilter::SqlFilter(WhereJoint joint, QString field, WhereOperator oper, QVariantList values) :
  _field(field), _values(values), _oper(oper), _joint(joint)
{

}

WhereJoint SqlFilter::joint()
{
  return _joint;
}

QString SqlFilter::toString() const
{
  QString filterStr;
  QString pattern = "%1 %2 %3 ";

  switch (_oper) {
  case WhereOperator::Equals:
  case WhereOperator::NotEquals: {
    bool positive = (_oper == WhereOperator::Equals);
    if (_values.count() > 1) {
      QString op = positive ? "in" : "not in";
      QStringList vals;
      foreach (QVariant val, _values) {
        vals.append(strVal(val));
      }
      filterStr.append(pattern.arg(_field).arg(op).arg("(" + vals.join(",") + ")"));
    }
    else {
      QString op = positive ? "=" : "<>";
      filterStr.append(pattern.arg(_field).arg(op).arg(strVal(_values.first())));
    }
    break;
  }
  case WhereOperator::IsNull:
  case WhereOperator::IsNotNull: {
    bool positive = (_oper == WhereOperator::IsNull);
    QString op = positive ? "is" : "is not";
    filterStr.append(pattern.arg(_field).arg(op).arg("NULL"));
    break;
  }
  case WhereOperator::MoreThan:
  case WhereOperator::LessThan: {
    QString op = (_oper == WhereOperator::MoreThan) ? ">" : "<";
    filterStr.append(pattern.arg(_field).arg(op).arg(strVal(_values.first())));
    break;
  }
  case WhereOperator::Between:
    filterStr.append("between").append(" ").append(strVal(_values.first())).append(" ").append("and")
        .append(" ").append(strVal(_values.at(1))).append(" ");
    break;
  }

  return filterStr;
}

QString SqlFilter::strVal(QVariant value) const
{
  switch (value.type()) {
  case QVariant::Int:
  case QVariant::Bool:
    return value.toString();
  default:
    return "'" + value.toString() + "'";
  }
}

int SqlFilterManager::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent)
  return _filters.count();
}

QVariant SqlFilterManager::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();
  if (role == Qt::DisplayRole) {
    return _filters.at(index.row()).toString();
  }
  return QVariant();
}
