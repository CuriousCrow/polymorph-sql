#include "strutils.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QRegularExpression>


#define VAL_BRACKETS "#"

StrUtils::StrUtils(){}

QString StrUtils::fillValues(QString templ, QMap<QString, QString> valuesMap)
{
    foreach (QString key, valuesMap.keys()) {
        QString val = valuesMap.value(key);
        if (val.isEmpty()) {
            val = "NULL";
        }
        else {
            bool isNumber = false;
            val.toLongLong(&isNumber);
            if (!isNumber)
                val = "'" + val + "'";
        }
        templ = templ.replace(VAL_BRACKETS + key + VAL_BRACKETS, val);
    }
    return templ;
}

QString StrUtils::intToBitmask(int intVal)
{
  return QString::number(intVal, 2);
}

QString StrUtils::md5(QByteArray str)
{
  return QCryptographicHash::hash(str, QCryptographicHash::Md5).toHex();
}

QList<qlonglong> StrUtils::longToList(qlonglong longVal)
{
    QList<qlonglong> resList;
    QString strMask = QString::number(longVal, 2);
//    qDebug() << longVal << strMask;
    for(int i=0; i<strMask.length(); i++) {
        if (strMask.at(strMask.length()-1-i) == '1')
            resList.append(pow(2,i));
    }
    return resList;
}

QString StrUtils::replaceTag(QString inStr, QString tagName, QString templ)
{
    QRegularExpression rx;
    rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption | QRegularExpression::InvertedGreedinessOption);
    QString pattern = "<%1 ([^>]*)>(.*)</%1>";
    rx.setPattern(pattern.arg(tagName));
    int pos = 0;
    QStringList linksInTempl = dashValues(templ);
    QRegularExpressionMatchIterator i = rx.globalMatch(inStr);
    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        qDebug() << "Regexp res:" << match.captured(1) << match.captured(2);
        QString replaceStr = templ;
        QHash<QString, QString> attrHash = attrsToHash(match.captured(1));
        attrHash.insert("text", match.captured(2));
        foreach (QString link, linksInTempl) {
            QStringList attrLinks = link.split('/', Qt::SkipEmptyParts);
            bool attrFound = false;
            foreach (QString attrName, attrLinks) {
                if (attrHash.contains(attrName)) {
                    replaceStr = replaceStr.replace("#" + link + "#", attrHash.value(attrName));
                    attrFound = true;
                    break;
                }
            }
            if (!attrFound) {
                replaceStr = replaceStr.replace("#" + link + "#", "неизв.");
            }
        }

        foreach (QString name, attrHash.keys()) {
            replaceStr = replaceStr.replace("#" + name + "#", attrHash.value(name));
        }
        QString cap = match.captured();
        int capLength = cap.length();
        inStr = inStr.replace(pos, capLength, replaceStr);
    }
    rx.setPattern("");
    return inStr;
}

QHash<QString, QString> StrUtils::attrsToHash(QString attrs)
{
    QHash<QString, QString> resHash;

    bool inQuotes = false;
    QString currentAttr;
    QStringList attrList;
    foreach (QChar chr, attrs.trimmed()) {
        if (chr == '"') {
          inQuotes = !inQuotes;
          continue;
        }
        if (chr == ' ' && !inQuotes) {
            if (!currentAttr.isEmpty()) {
                attrList.append(currentAttr);
                currentAttr.clear();
            }
            continue;
        }
        currentAttr.append(chr);
    }
    if (!currentAttr.isEmpty())
        attrList.append(currentAttr);

    foreach (QString attrStr, attrList) {
        QString name = attrStr.section('=', 0, 0).trimmed();
        QString value = attrStr.section("=", 1, 1).remove("\"").trimmed();
        resHash.insert(name, value);
    }
    return resHash;
}

QStringList StrUtils::dashValues(QString inStr)
{
    QStringList resVals;
    QRegularExpression rx("#([a-z/]+)#");
    QRegularExpressionMatchIterator i = rx.globalMatch(inStr);
    while(i.hasNext()) {
      QRegularExpressionMatch match = i.next();
      resVals.append(match.captured(1));
    }
    return resVals;
}

bool lessThanByLength(QString &str1, QString &str2)
{
    return str1.length() < str2.length();
}

bool greaterThanByLength(QString &str1, QString &str2)
{
    return str1.length() > str2.length();
}
