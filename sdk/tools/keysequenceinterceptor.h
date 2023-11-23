#ifndef KEYSEQUENCEINTERCEPTOR_H
#define KEYSEQUENCEINTERCEPTOR_H

#include <QObject>

#include <QObject>
#include <QMap>
#include <QKeySequence>

class KeySequence : public QKeySequence
{
 public:
    KeySequence(const QString &key, SequenceFormat format = NativeText);
    KeySequence(int k1, int k2 = 0, int k3 = 0, int k4 = 0);
    KeySequence(const QKeySequence &ks);
    KeySequence(StandardKey key);
};

inline bool operator==(const KeySequence &ks1, const KeySequence &ks2)
{
    return ks1.matches(ks2);
}

inline bool operator<(const KeySequence &ks1, const KeySequence &ks2)
{
    Q_UNUSED(ks1)
    Q_UNUSED(ks2)
    //TODO:
    return false;
//    return ks1[0] < ks2[0];
}

inline uint qHash(const KeySequence &key, uint seed)
{
    return qHash(key[0], seed) ^ qHash(key[1], seed) ^ qHash(key[2], seed) ^ qHash(key[3]);
}

class AbstractKeySequenceHandler : public QObject
{
    Q_OBJECT
public:
    AbstractKeySequenceHandler();
    virtual ~AbstractKeySequenceHandler();
    virtual QSet<KeySequence> keySequences() = 0;
    virtual bool handle(const KeySequence &keySequence) = 0;
};


class KeySequenceInterceptor : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE KeySequenceInterceptor(QObject *parent = nullptr);
    void attachToWidget(QWidget *widget);
    void registerHandler(KeySequence keySequence, AbstractKeySequenceHandler* keyHandler);
    void registerHandler(AbstractKeySequenceHandler* keyHandler);
    QList<AbstractKeySequenceHandler*> handlers() const;
signals:

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);
private:
    QMap<KeySequence, AbstractKeySequenceHandler*> _handlerHash;
};
#endif // KEYSEQUENCEINTERCEPTOR_H
