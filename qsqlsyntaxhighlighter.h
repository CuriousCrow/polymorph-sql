#ifndef QSQLSYNTAXHIGHLIGHTER_H
#define QSQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class QSqlSyntaxHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  QSqlSyntaxHighlighter(QObject *parent);
  ~QSqlSyntaxHighlighter();

  QStringList keyWords();
  QStringList functions();

  // QSyntaxHighlighter interface
protected:
  virtual void highlightBlock(const QString &text);
private:
  void highlightKeywords(const QString &text);
  void highlightFunctions(const QString &text);
  QStringList _sqlKeyWords;
  QStringList _sqlFunctions;
};

#endif // QSQLSYNTAXHIGHLIGHTER_H
