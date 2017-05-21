#include "qsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include "qknowledgebase.h"
#include <QSqlTableModel>
#include "lsqltablemodel.h"

QSqlSyntaxHighlighter::QSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
  //TODO: Keywords should be loaded depending on database type
  LSqlTableModel* mKeywords = QKnowledgeBase::kb()->mKeywords;
  for (int i=0; i<mKeywords->rowCount(); i++){
    _sqlKeyWords << mKeywords->data(mKeywords->index(i, mKeywords->fieldIndex("NAME"))).toString().toUpper();
  }
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
