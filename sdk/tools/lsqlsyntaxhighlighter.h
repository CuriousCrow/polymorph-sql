#ifndef LSQLSYNTAXHIGHLIGHTER_H
#define LSQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include "core/lknowledgebase.h"

class LSqlSyntaxHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT
public:
  Q_INVOKABLE LSqlSyntaxHighlighter(QObject *parent = nullptr);
  ~LSqlSyntaxHighlighter();

  QStringList keyWords();
  QStringList functions();

  Q_INVOKABLE void inject_by_kb(LKnowledgeBase* kb);
  void updateModels(QString driverName);

  // QSyntaxHighlighter interface
protected:
  virtual void highlightBlock(const QString &text);
private:
  void highlightKeywords(const QString &text);
  void highlightFunctions(const QString &text);
  void highlightComments(const QString &text);
  LKnowledgeBase* _kb;
  QStringList _sqlKeyWords;
  QStringList _sqlFunctions;
};

#endif // LSQLSYNTAXHIGHLIGHTER_H
