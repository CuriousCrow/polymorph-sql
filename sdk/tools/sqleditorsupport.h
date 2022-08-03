#ifndef SQLEDITORSUPPORT_H
#define SQLEDITORSUPPORT_H

#include <QObject>
#include "tools/lsqlsyntaxhighlighter.h"
#include "utils/lsimpletooltip.h"
#include "core/sqlhelplookupprovider.h"
#include "tools/simplesqlcompletersupport.h"
#include "objects/dbdatabaseitem.h"
#include "widgets/lqueryeditor.h"


//class LKeySequenceInterceptor : public QObject
//{
//  Q_OBJECT
//public:
//  LKeySequenceInterceptor(QObject* parent = Q_NULLPTR);
//  void setKeySequence(QKeySequence keySequence);
//  void applyToWidget(QWidget* widget);
//private:
//  QKeySequence _keySequence;
//signals:
//  void keySequencePressed(QKeySequence keySequence);
//public:
//  virtual bool eventFilter(QObject *watched, QEvent *event);
//};

class SqlEditorSupport : public QObject
{
  Q_OBJECT
public:
  Q_INVOKABLE SqlEditorSupport();

  void updateModels(DBObjectItem* dbItem);
  void setEditor(QPlainTextEdit* editor);

protected:
  Q_INVOKABLE void inject_sqlCompleterSupport_into_form(SimpleSqlCompleterSupport* completerSupport);
  Q_INVOKABLE void inject_helpLookupProvider(SqlHelpLookupProvider* lookupProvider);
  Q_INVOKABLE void inject_by_sqlSyntaxHighlighter(LSqlSyntaxHighlighter* syntaxHighlighter);
  QString currentWord();
  QString previousWord();
  QPoint cursorGlobalPos();
private slots:
  void onHelpKey();

private:
  QPlainTextEdit* _editor;
  SimpleSqlCompleterSupport* _completerSupport;
  LSqlSyntaxHighlighter* _highlighter;
  LSimpleTooltip* _helpTooltip;
  SqlHelpLookupProvider* _helpLookupProvider;
  LKeySequenceInterceptor* _keyInterceptor;
};

#endif // SQLEDITORSUPPORT_H
