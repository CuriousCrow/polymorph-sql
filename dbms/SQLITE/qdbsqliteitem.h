#ifndef QDBSQLITEITEM_H
#define QDBSQLITEITEM_H

#include "../qdbdatabaseitem.h"

class QDBSqliteItem : public QDBDatabaseItem
{
    Q_OBJECT
public:
    QDBSqliteItem(QString caption, QObject* parent = 0);

public:
    virtual bool loadChildren();
};

#endif // QDBSQLITEITEM_H
