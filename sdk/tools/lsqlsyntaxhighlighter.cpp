#include "lsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include <QSqlTableModel>
#include "models/lsqltablemodel.h"

LSqlSyntaxHighlighter::LSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
}

LSqlSyntaxHighlighter::~LSqlSyntaxHighlighter()
{
}

QStringList LSqlSyntaxHighlighter::keyWords()
{
  return _sqlKeyWords;
}

QStringList LSqlSyntaxHighlighter::functions()
{
    return _sqlFunctions;
}

void LSqlSyntaxHighlighter::inject_by_kb(LKnowledgeBase *kb)
{
    //TODO: Keywords should be loaded depending on database type
    LSqlTableModel* mKeywords = kb->mKeywords;
    for (int i=0; i<mKeywords->rowCount(); i++){
      _sqlKeyWords << mKeywords->data(mKeywords->index(i, mKeywords->fieldIndex("NAME"))).toString().toUpper();
    }
    LSqlTableModel* mFunctions = kb->mFunctions;
    int nameCol = mFunctions->fieldIndex("NAME");
    for (int i=0; i<mFunctions->rowCount(); i++) {
      _sqlFunctions << mFunctions->data(mFunctions->index(i, nameCol)).toString().toLower();
    }
}

void LSqlSyntaxHighlighter::highlightBlock(const QString &text)
{
  highlightKeywords(text);
  highlightFunctions(text);
}

void LSqlSyntaxHighlighter::highlightKeywords(const QString &text)
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
            //apply format on found string
            setFormat(match.capturedStart(capNum), match.capturedLength(capNum), format);
        }
    }
}

void LSqlSyntaxHighlighter::highlightFunctions(const QString &text)
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
        //apply format on found string
        setFormat(match.capturedStart(capNum), match.capturedLength(capNum), format);
    }
  }
}
