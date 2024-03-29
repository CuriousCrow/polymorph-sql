#ifndef LQUERYEDITOR_H
#define LQUERYEDITOR_H

#include <QKeySequence>
#include <QPlainTextEdit>

class LKeySequenceInterceptor : public QObject
{
  Q_OBJECT
public:
  LKeySequenceInterceptor(QObject* parent = Q_NULLPTR);
  void setKeySequence(QKeySequence keySequence);
  void applyToWidget(QWidget* widget);
private:
  QKeySequence _keySequence;
signals:
  void keySequencePressed(QKeySequence keySequence);
public:
  virtual bool eventFilter(QObject *watched, QEvent *event);
};

class LMousePressedInterceptor : public QObject
{
  Q_OBJECT
public:
  LMousePressedInterceptor(QObject* parent = Q_NULLPTR);

  // QObject interface
public:
  bool eventFilter(QObject *watched, QEvent *event);
};

class LQueryEditor : public QPlainTextEdit
{
  Q_OBJECT
public:
  LQueryEditor(QWidget *parent = Q_NULLPTR);
  QString currentWord();
  QString previousWord();
  QPoint cursorGlobalPos();
signals:
  void wordClicked(QString word, Qt::KeyboardModifiers modifiers);
  void infoMessage(const QString &message);
  // QWidget interface
protected:
  void mousePressEvent(QMouseEvent *event) override;
  virtual void dropEvent(QDropEvent *event) override;
};

#endif // LQUERYEDITOR_H
