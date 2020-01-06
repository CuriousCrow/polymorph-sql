#include "sqlfiltermanager.h"

SqlFilterManager::SqlFilterManager(QObject* parent) : QObject(parent)
{
}

void SqlFilterManager::addEqualFilter(QString field, QVariant value, bool exclude, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  _filters.append(SqlFilter(joint, field, exclude ? WhereOperator::NotEquals : WhereOperator::Equals, values));
}

void SqlFilterManager::addEqualFilter(QString field, QVariantList values, bool exclude, WhereJoint joint)
{
  _filters.append(SqlFilter(joint, field, exclude ? WhereOperator::NotEquals : WhereOperator::Equals, values));
}

void SqlFilterManager::addNullFilter(QString field, bool exclude, WhereJoint joint)
{
  _filters.append(SqlFilter(joint, field, exclude ? WhereOperator::IsNotNull : WhereOperator::IsNull, QVariantList()));
}

void SqlFilterManager::addMoreThanFilter(QString field, QVariant value, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  _filters.append(SqlFilter(joint, field, WhereOperator::MoreThan, values));
}

void SqlFilterManager::addLessThanFilter(QString field, QVariant value, WhereJoint joint)
{
  QVariantList values;
  values.append(value);
  _filters.append(SqlFilter(joint, field, WhereOperator::LessThan, values));
}

void SqlFilterManager::addBetweenFilter(QString field, QVariant fromValue, QVariant toValue, WhereJoint joint)
{
  QVariantList values;
  values.append(fromValue);
  values.append(toValue);
  _filters.append(SqlFilter(joint, field, WhereOperator::Between, values));
}

void SqlFilterManager::clear()
{
  _filters.clear();
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

SqlFilter::SqlFilter(WhereJoint joint, QString field, WhereOperator oper, QVariantList values) :
  _field(field), _values(values), _oper(oper), _joint(joint)
{

}

WhereJoint SqlFilter::joint()
{
  return _joint;
}

QString SqlFilter::toString()
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

QString SqlFilter::strVal(QVariant value)
{
  switch (value.type()) {
  case QVariant::Int:
  case QVariant::Bool:
    return value.toString();
  default:
    return "'" + value.toString() + "'";
  }
}
