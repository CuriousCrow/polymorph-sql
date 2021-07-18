#include "qsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include "../core/qknowledgebase.h"
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

    QRegularExpression rx;
    rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    QString pattern = "\\b(%1)\\b";

    foreach (QString keyword, _sqlKeyWords){
        Q_ASSERT(!keyword.isEmpty());

        rx.setPattern(pattern.arg(keyword));

        QRegularExpressionMatchIterator i = rx.globalMatch(text);
        while(i.hasNext()) {
            QRegularExpressionMatch match = i.next();
            int capNum = (rx.captureCount() == 0) ? 0 : 1;
            //применение формата на найденную подстроку
            setFormat(match.capturedStart(capNum), match.capturedLength(capNum), format);
        }
    }
}

void QSqlSyntaxHighlighter::highlightFunctions(const QString &text)
{
  QTextCharFormat format;
  format.setFontItalic(true);

  QRegularExpression rx;
  rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
  QString pattern = "\\b(%1)\\(";

  foreach (QString function, _sqlFunctions){
    Q_ASSERT(!function.isEmpty());

    rx.setPattern(pattern.arg(function));

    QRegularExpressionMatchIterator i = rx.globalMatch(text);
    while(i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        int capNum = (rx.captureCount() == 0) ? 0 : 1;
        //применение формата на найденную подстроку
        setFormat(match.capturedStart(capNum), match.capturedLength(capNum), format);
    }
  }
}
