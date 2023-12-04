#ifndef MYSQLSEQUENCE_H
#define MYSQLSEQUENCE_H

#include <QObject>
#include "objects/dbsequence.h"

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
