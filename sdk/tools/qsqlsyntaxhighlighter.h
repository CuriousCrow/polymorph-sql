#ifndef QSQLSYNTAXHIGHLIGHTER_H
#define QSQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include "../core/qknowledgebase.h"

class QSqlSyntaxHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  Q_INVOKABLE QSqlSyntaxHighlighter(QObject *parent = nullptr);
  ~QSqlSyntaxHighlighter();

  QStringList keyWords();
  QStringList functions();

  Q_INVOKABLE void inject_by_kb(QKnowledgeBase* kb);

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
