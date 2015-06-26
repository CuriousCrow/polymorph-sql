#ifndef QSQLSYNTAXHIGHLIGHTER_H
#define QSQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QSqlSyntaxHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  QSqlSyntaxHighlighter(QObject *parent);
  ~QSqlSyntaxHighlighter();

  QStringList keyWords();

  // QSyntaxHighlighter interface
protected:
  virtual void highlightBlock(const QString &text);
private:
  QStringList _sqlKeyWords;
};

#endif // QSQLSYNTAXHIGHLIGHTER_H
