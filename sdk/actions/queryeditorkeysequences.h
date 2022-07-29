#ifndef QUERYEDITORKEYSEQUENCES_H
#define QUERYEDITORKEYSEQUENCES_H

#include <QObject>
#include "core/extensions.h"
#include "core/extensionpoints.h"
#include "widgets/lqueryeditor.h"
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
  virtual QSet<KeySequence> keySequences() override;
  virtual bool handle(const KeySequence &keySequence) override;
};

class QueryEditorKeyHandler : public AbstractKeySequenceHandler
{
  Q_OBJECT
public:
  void setEditor(LQueryEditor* editor);
protected:
  LQueryEditor* _editor;
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
  virtual QSet<KeySequence> keySequences() override;
  virtual bool handle(const KeySequence &keySequence) override;
};

#endif // QUERYEDITORKEYSEQUENCES_H
