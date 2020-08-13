#ifndef SQLUTILS_H
#define SQLUTILS_H

#include <QObject>

QT_BEGIN_NAMESPACE

class QSqlHelper
{
public:
  // SQL keywords
  inline const static QLatin1String as() { return QLatin1String("AS"); }
  inline const static QLatin1String asc() { return QLatin1String("ASC"); }
  inline const static QLatin1String comma() { return QLatin1String(","); }
  inline const static QLatin1String desc() { return QLatin1String("DESC"); }
  inline const static QLatin1String eq() { return QLatin1String("="); }
  // "and" is a C++ keyword
  inline const static QLatin1String et() { return QLatin1String("AND"); }
  inline const static QLatin1String from() { return QLatin1String("FROM"); }
  inline const static QLatin1String leftJoin() { return QLatin1String("LEFT JOIN"); }
  inline const static QLatin1String on() { return QLatin1String("ON"); }
  inline const static QLatin1String orderBy() { return QLatin1String("ORDER BY"); }
  inline const static QLatin1String parenClose() { return QLatin1String(")"); }
  inline const static QLatin1String parenOpen() { return QLatin1String("("); }
  inline const static QLatin1String select() { return QLatin1String("SELECT"); }
  inline const static QLatin1String sp() { return QLatin1String(" "); }
  inline const static QLatin1String where() { return QLatin1String("WHERE"); }
  inline const static QLatin1String is() { return QLatin1String("IS"); }
  inline const static QLatin1String null() { return QLatin1String("NULL"); }

  // Build expressions based on key words
  inline const static QString as(const QString &a, const QString &b) { return b.isEmpty() ? a : concat(concat(a, as()), b); }
  inline const static QString asc(const QString &s) { return concat(s, asc()); }
  inline const static QString comma(const QString &a, const QString &b) { return a.isEmpty() ? b : b.isEmpty() ? a : QString(a).append(comma()).append(b); }
  inline const static QString concat(const QString &a, const QString &b) { return a.isEmpty() ? b : b.isEmpty() ? a : QString(a).append(sp()).append(b); }
  inline const static QString desc(const QString &s) { return concat(s, desc()); }
  inline const static QString eq(const QString &a, const QString &b) { return QString(a).append(eq()).append(b); }
  inline const static QString et(const QString &a, const QString &b) { return a.isEmpty() ? b : b.isEmpty() ? a : concat(concat(a, et()), b); }
  inline const static QString from(const QString &s) { return concat(from(), s); }
  inline const static QString leftJoin(const QString &s) { return concat(leftJoin(), s); }
  inline const static QString on(const QString &s) { return concat(on(), s); }
  inline const static QString orderBy(const QString &s) { return s.isEmpty() ? s : concat(orderBy(), s); }
  inline const static QString paren(const QString &s) { return s.isEmpty() ? s : parenOpen() + s + parenClose(); }
  inline const static QString select(const QString &s) { return concat(select(), s); }
  inline const static QString where(const QString &s) { return s.isEmpty() ? s : concat(where(), s); }
  inline const static QString isNull(const QString &s) { return concat(s, concat(is(),null())); }
};

QT_END_NAMESPACE

typedef QSqlHelper Sql;

#endif // SQLUTILS_H
