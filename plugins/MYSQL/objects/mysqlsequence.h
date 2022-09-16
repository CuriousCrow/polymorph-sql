#ifndef MYSQLSEQUENCE_H
#define MYSQLSEQUENCE_H

#include "objects/dbsequence.h"
#include <QObject>

class MysqlSequence : public DBSequenceItem
{
    Q_OBJECT
public:
    Q_INVOKABLE MysqlSequence();

    // DBObjectItem interface
public:
    virtual bool refresh() override;
};

#endif // MYSQLSEQUENCE_H
