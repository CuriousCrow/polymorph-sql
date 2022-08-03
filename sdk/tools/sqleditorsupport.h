#ifndef SQLEDITORSUPPORT_H
#define SQLEDITORSUPPORT_H

#include <QObject>
#include "tools/lsqlsyntaxhighlighter.h"
#include "utils/lsimpletooltip.h"
#include "core/sqlhelplookupprovider.h"
#include "core/extensions.h"
#include "tools/simplesqlcompletersupport.h"
#include "objects/dbdatabaseitem.h"
#include "widgets/lqueryeditor.h"
#include "tools/keysequenceinterceptor.h"
#include "actions/queryeditorkeysequences.h"


class HelpKeyHandler : public SlotQueryEditorKeyHandler
{
  Q_OBJECT
  // AbstractKeySequenceHandler interface
public:
  virtual QSet<KeySequence> keySequences() override;
};

class SqlEditorSupport : public QObject, public Extensible
{
  Q_OBJECT
public:
  Q_INVOKABLE SqlEditorSupport();

  void updateModels(DBObjectItem* dbItem);
  void setEditor(QPlainTextEdit* editor);
  LDBObjectTableModel* objects();

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
  KeySequenceInterceptor* _keyInterceptor;

  // Extensible interface
public:
  virtual void injectExtension(ExtensionPoint ep, QObject *e) override;
};

#endif // SQLEDITORSUPPORT_H
