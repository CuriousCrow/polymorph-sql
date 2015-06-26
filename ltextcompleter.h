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
public:
  LTextCompleter(QObject *parent = 0);
  LTextCompleter(QAbstractItemModel *model, QObject *parent = 0);
  LTextCompleter(const QStringList& completions, QObject *parent = 0);
  ~LTextCompleter();
  virtual bool eventFilter(QObject *o, QEvent *e);

  int minCompletionPrefixLength() const;
  void setMinCompletionPrefixLength(int minCompletionPrefixLength);
private:
  int _minCompletionPrefixLength = 1;
  bool isMultilineEditor();
  QTextCursor textCursor();
  QRect cursorRect();
  void setTextCursor(QTextCursor cursor);
};

#endif // QTEXTCOMPLETER_H
