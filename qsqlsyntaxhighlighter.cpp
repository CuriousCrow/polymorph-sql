#include "qsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include "qknowledgebase.h"
#include <QSqlTableModel>
#include "models/lsqltablemodel.h"

QSqlSyntaxHighlighter::QSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
  //TODO: Keywords should be loaded depending on database type
  LSqlTableModel* mKeywords = QKnowledgeBase::kb()->mKeywords;
  for (int i=0; i<mKeywords->rowCount(); i++){
    _sqlKeyWords << mKeywords->data(mKeywords->index(i, mKeywords->fieldIndex("NAME"))).toString().toUpper();
  }
  LSqlTableModel* mFunctions = QKnowledgeBase::kb()->mFunctions;
  int nameCol = mFunctions->fieldIndex("NAME");
  for (int i=0; i<mFunctions->rowCount(); i++) {
    _sqlFunctions << mFunctions->data(mFunctions->index(i, nameCol)).toString().toLower();
  }
}

QSqlSyntaxHighlighter::~QSqlSyntaxHighlighter()
{
}

QStringList QSqlSyntaxHighlighter::keyWords()
{
  return _sqlKeyWords;
}

QStringList QSqlSyntaxHighlighter::functions()
{
  return _sqlFunctions;
}

void QSqlSyntaxHighlighter::highlightBlock(const QString &text)
{
  highlightKeywords(text);
  highlightFunctions(text);
}

void QSqlSyntaxHighlighter::highlightKeywords(const QString &text)
{
  QTextCharFormat format;
  format.setFontWeight(QFont::Bold);

  QRegExp rx;
  rx.setCaseSensitivity(Qt::CaseInsensitive);

  QString pattern = "\\b(%1)\\b";

  foreach (QString keyword, _sqlKeyWords){
    Q_ASSERT(!keyword.isEmpty());

    rx.setPattern(pattern.arg(keyword));

    int index = rx.indexIn(text, 0);
    while (index >= 0){
      //применение формата на найденную подстроку
      setFormat(rx.pos(1), rx.cap(1).length(), format);
      index = rx.indexIn(text, rx.pos(1) + rx.cap(1).length());
    }
  }
}

void QSqlSyntaxHighlighter::highlightFunctions(const QString &text)
{
  QTextCharFormat format;
  format.setFontItalic(true);

  QRegExp rx;
  rx.setCaseSensitivity(Qt::CaseInsensitive);
  QString pattern = "\\b(%1)\\(";

  foreach (QString function, _sqlFunctions){
    Q_ASSERT(!function.isEmpty());

    rx.setPattern(pattern.arg(function));

    int index = rx.indexIn(text, 0);
    while (index >= 0){
      //применение формата на найденную подстроку
      setFormat(rx.pos(1), rx.cap(1).length(), format);
      index = rx.indexIn(text, rx.pos(1) + rx.cap(1).length());
    }
  }
}
