#ifndef ABSTRACTUSERCONTEXT_H
#define ABSTRACTUSERCONTEXT_H

#include <QObject>

class AbstractUserContext : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE AbstractUserContext(QObject *parent = nullptr);

signals:
    void contextChanged();
};

class FocusWidgetContext : public AbstractUserContext
{
    Q_OBJECT
public:
    void setFocusedWidget(QWidget* widget);
};

#endif // ABSTRACTUSERCONTEXT_H
