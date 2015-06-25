#include "qsqlsyntaxhighlighter.h"
#include <QTextCharFormat>

QSqlSyntaxHighlighter::QSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
  //TODO: Keywords should be loaded depending on database type
  _sqlKeyWords << "SELECT" << "FROM" << "WHERE" << "INSERT" << "INTO" << "ORDER"
               << "BY" << "ASC" << "DESC" << "UPDATE" << "DELETE" << "CREATE"
               << "OR" << "AND" << "DISTINCT" << "TABLE";

}

QSqlSyntaxHighlighter::~QSqlSyntaxHighlighter()
{
}

void QSqlSyntaxHighlighter::highlightBlock(const QString &text)
{
  QTextCharFormat format;
  format.setFontWeight(QFont::Bold);

  foreach (QString keyword, _sqlKeyWords){
    int index = text.indexOf(keyword, 0, Qt::CaseInsensitive);
    while (index >= 0){
        int length = keyword.length();
        //применение формата на найденную подстроку
        setFormat(index, length, format);
        index = text.indexOf(keyword, index + length, Qt::CaseInsensitive);
    }
  }
}
