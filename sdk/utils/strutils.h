#ifndef STRUTILS_H
#define STRUTILS_H

#include <QHash>
#include <QMap>
#include <QString>
#include "math.h"

class StrUtils
{
public:
    static QString fillValues(QString templ, QMap<QString, QString> valuesMap);
    static QString intToBitmask(int intVal);
    static QString md5(QByteArray str);
    static QList<qlonglong> longToList(qlonglong longVal);
    static QString replaceTag(QString inStr, QString tagName, QString templ);
    static QHash<QString, QString> attrsToHash(QString attrs);
    static QStringList dashValues(QString inStr);
private:
    StrUtils();
};

bool lessThanByLength(QString &str1, QString &str2);
bool greaterThanByLength(QString &str1, QString &str2);

#endif // STRUTILS_H
