#include "qsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>

QSqlSyntaxHighlighter::QSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
  //TODO: Keywords should be loaded depending on database type
  _sqlKeyWords << "SELECT" << "FROM" << "WHERE" << "INSERT" << "INTO" << "ORDER"
               << "BY" << "ASC" << "DESC" << "UPDATE" << "DELETE" << "CREATE"
               << "OR" << "AND" << "DISTINCT" << "TABLE" << "VALUES";

}

QSqlSyntaxHighlighter::~QSqlSyntaxHighlighter()
{
}

QStringList QSqlSyntaxHighlighter::keyWords()
{
  return _sqlKeyWords;
}

void QSqlSyntaxHighlighter::highlightBlock(const QString &text)
{
  QTextCharFormat format;
  format.setFontWeight(QFont::Bold);   

  QRegExp rx;
  rx.setCaseSensitivity(Qt::CaseInsensitive);

  foreach (QString keyword, _sqlKeyWords){
    rx.setPattern("(?:^|\\s)(" + keyword + ")(?:$|\\s)");

    int index = rx.indexIn(text, 0);
    while (index >= 0){      
      int capNum = (rx.captureCount() == 0) ? 0 : 1;
        //применение формата на найденную подстроку
      setFormat(rx.pos(capNum), rx.cap(capNum).length(), format);
      index = rx.indexIn(text, rx.pos(capNum) + rx.cap(capNum).length());
    }
  }
}
