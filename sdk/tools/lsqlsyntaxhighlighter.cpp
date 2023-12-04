#include "lsqlsyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QDebug>
#include <QSqlTableModel>
#include <QColor>
#include "objects/appconst.h"

LSqlSyntaxHighlighter::LSqlSyntaxHighlighter(QObject *parent):
  QSyntaxHighlighter(parent)
{
}

LSqlSyntaxHighlighter::~LSqlSyntaxHighlighter()
{
  qDebug() << "LSqlSyntaxHighlighter destructor";
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
  _kb = kb;
}

void LSqlSyntaxHighlighter::updateModels(QString driverName)
{
  LDBObjectTableModel* mKeywords = _kb->modelByType(OBJTYPE_KEYWORD, driverName);
  int nameCol = mKeywords->colByName(F_NAME);
  for (int i=0; i<mKeywords->rowCount(); i++){
    _sqlKeyWords << mKeywords->data(i, nameCol).toString().toUpper();
  }
  LDBObjectTableModel* mFunctions = _kb->modelByType(OBJTYPE_FUNCTION, driverName);
  for (int i=0; i<mFunctions->rowCount(); i++) {
    _sqlFunctions << mFunctions->data(i, nameCol).toString().toLower();
  }
}

void LSqlSyntaxHighlighter::highlightBlock(const QString &text)
{
  highlightKeywords(text);
  highlightFunctions(text);
  highlightComments(text);
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

void LSqlSyntaxHighlighter::highlightComments(const QString &text)
{
  QTextCharFormat format;
  format.setFontItalic(true);

  QRegularExpression rx;
  rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
  rx.setPattern("-- .*(?:\\n|$)");


  QRegularExpressionMatchIterator i = rx.globalMatch(text);
  while(i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    int capNum = (rx.captureCount() == 0) ? 0 : 1;
    //apply format on found string
    setFormat(match.capturedStart(capNum), match.capturedLength(capNum), QColor(Qt::gray));
  }
}
