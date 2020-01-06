#ifndef SQLFILTERMANAGER_H
#define SQLFILTERMANAGER_H

#include <QList>
#include <QObject>

enum WhereOperator {
  Equals,
  NotEquals,
  MoreThan,
  LessThan,
  IsNull,
  IsNotNull,
  Between
};

enum WhereJoint {
  None,
  And,
  Or
};

class SqlFilter
{
public:
  SqlFilter(WhereJoint joint, QString field, WhereOperator oper, QVariantList values);
  WhereJoint joint();
  QString toString();
private:
  QString _field;
  QVariantList _values;
  WhereOperator _oper;
  WhereJoint _joint;
  QString strVal(QVariant value);
};

class SqlFilterManager : public QObject
{
  Q_OBJECT
public:
  SqlFilterManager(QObject* parent = nullptr);
  void addEqualFilter(QString field, QVariant value, bool exclude = false, WhereJoint joint = WhereJoint::And);
  void addEqualFilter(QString field, QVariantList values, bool exclude = false, WhereJoint joint = WhereJoint::And);
  void addNullFilter(QString field, bool exclude = false, WhereJoint joint = WhereJoint::And);
  void addMoreThanFilter(QString field, QVariant value, WhereJoint joint = WhereJoint::And);
  void addLessThanFilter(QString field, QVariant value, WhereJoint joint = WhereJoint::And);
  void addBetweenFilter(QString field, QVariant fromValue, QVariant toValue, WhereJoint joint = WhereJoint::And);
  void clear();
  QString whereClause();
private:
  QList<SqlFilter> _filters;
};

#endif // SQLFILTERMANAGER_H
