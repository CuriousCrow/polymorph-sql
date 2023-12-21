#ifndef KEYSEQUENCEINTERCEPTOR_H
#define KEYSEQUENCEINTERCEPTOR_H

#include <QObject>

#include <QObject>
#include <QMap>
#include <QKeySequence>

#include <QDebug>

typedef void (*KeyHandlerFunc)(const QKeySequence &keySequence);

class AbstractKeySequenceHandler : public QObject
{
    Q_OBJECT
public:
    AbstractKeySequenceHandler();
    virtual ~AbstractKeySequenceHandler();
    virtual QSet<QKeySequence> keySequences() = 0;
    virtual bool handle(const QKeySequence &keySequence) = 0;
};

class KeySequenceHandlerWrapper : public AbstractKeySequenceHandler {
public:
    KeySequenceHandlerWrapper(KeyHandlerFunc handerFunc);

    // AbstractKeySequenceHandler interface
public:
    virtual QSet<QKeySequence> keySequences() override;
    virtual bool handle(const QKeySequence &keySequence) override;
private:
    KeyHandlerFunc _handlerFunc;
};


class KeySequenceInterceptor : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE KeySequenceInterceptor(QObject *parent = nullptr);
    void attachToWidget(QWidget *widget);
    void registerHandler(QKeySequence keySequence, AbstractKeySequenceHandler* keyHandler);
    void registerHandler(AbstractKeySequenceHandler* keyHandler);
    void registerHandler(QKeySequence keySequence, KeyHandlerFunc handlerFunc);
    QList<AbstractKeySequenceHandler*> handlers() const;
signals:

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    QMap<QKeySequence, AbstractKeySequenceHandler*> _handlerHash;
};
#endif // KEYSEQUENCEINTERCEPTOR_H
