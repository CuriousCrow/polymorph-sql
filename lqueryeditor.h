#ifndef LQUERYEDITOR_H
#define LQUERYEDITOR_H

#include <QPlainTextEdit>
#include <QKeySequence>

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

class LQueryEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    LQueryEditor(QWidget *parent = Q_NULLPTR);
    QString currentWord();
    QPoint cursorGlobalPos();
};

#endif // LQUERYEDITOR_H
