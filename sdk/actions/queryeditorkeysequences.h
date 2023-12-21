#ifndef QUERYEDITORKEYSEQUENCES_H
#define QUERYEDITORKEYSEQUENCES_H

#include <QObject>
#include <QPlainTextEdit>
#include "core/extensions.h"
#include "tools/keysequenceinterceptor.h"

class QETestHandler : public AbstractKeySequenceHandler, public AbstractExtension
{
  Q_OBJECT
public:
  Q_INVOKABLE QETestHandler();


  // AbstractExtension interface
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;

  // AbstractKeySequenceHandler interface
public:
  virtual QSet<QKeySequence> keySequences() override;
  virtual bool handle(const QKeySequence &keySequence) override;
};

class QueryEditorKeyHandler : public AbstractKeySequenceHandler
{
  Q_OBJECT
public:
  void setEditor(QPlainTextEdit* editor);
  QString currentWord();
  QString previousWord();
  QPoint cursorGlobalPos();
protected:
  QPlainTextEdit* _editor;
};

class SlotQueryEditorKeyHandler : public QueryEditorKeyHandler
{
  Q_OBJECT
  // AbstractKeySequenceHandler interface
public:
  virtual bool handle(const QKeySequence &keySequence) override;
signals:
  void keySignal(const QKeySequence &keySequence);
};

/** Toggles query editor line comments by Ctrl+/ key sequence */
class ToggleQueryCommentsHandler : public QueryEditorKeyHandler, public AbstractExtension
{
  Q_OBJECT
public:
  Q_INVOKABLE ToggleQueryCommentsHandler();

  // AbstractExtension interface
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;

  // AbstractKeySequenceHandler interface
public:
  virtual QSet<QKeySequence> keySequences() override;
  virtual bool handle(const QKeySequence &keySequence) override;
};

/** Generate table alias in query editor by Ctrl+T */
class GenerateTableAliasHandler : public QueryEditorKeyHandler, public AbstractExtension
{
  Q_OBJECT
public:
  Q_INVOKABLE GenerateTableAliasHandler();

  // AbstractKeySequenceHandler interface
public:
  virtual QSet<QKeySequence> keySequences() override;
  virtual bool handle(const QKeySequence &keySequence) override;

  // AbstractExtension interface
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint &extensionPoint) const override;
protected:
  QString generateAlias(QString tableName);
};

#endif // QUERYEDITORKEYSEQUENCES_H
