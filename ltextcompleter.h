#ifndef LTEXTCOMPLETER_H
#define LTEXTCOMPLETER_H

#include <QCompleter>
#include <QTextEdit>
#include <QPlainTextEdit>

/* Multiline editor text completer (supports QPlainTextEdit and QTextEdit)
  Completions view pops up by pressing <Ctrl>+<Space>
*/
class LTextCompleter : public QCompleter
{
  Q_OBJECT
public:
  LTextCompleter(QObject *parent = nullptr);
  LTextCompleter(QAbstractItemModel *model, QObject *parent = nullptr);
  LTextCompleter(const QStringList& completions, QObject *parent = nullptr);
  ~LTextCompleter();
  virtual bool eventFilter(QObject *o, QEvent *e);

  int minCompletionPrefixLength() const;
  void setMinCompletionPrefixLength(int minCompletionPrefixLength);
signals:
  void completerRequested(const QString &contextWord);
private:
  int _minCompletionPrefixLength = 1;
  int _popupWidth = 200;
  bool isMultilineEditor();
  QTextCursor textCursor();
  QRect cursorRect();
  void setTextCursor(QTextCursor cursor);
  bool tryToComplete(QString prefix, bool replaceIfOneOption = false);
  QString getCompletionPrefix();
  QString getCompletionContext();
};

#endif // QTEXTCOMPLETER_H
