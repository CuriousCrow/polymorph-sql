#ifndef FIREBIRDSEQUENCE_H
#define FIREBIRDSEQUENCE_H

#include "objects/dbsequenceitem.h"
#include <QObject>

class FirebirdSequence : public DBSequenceItem
{
    Q_OBJECT
public:
    Q_INVOKABLE FirebirdSequence();

    // DBObjectItem interface
public:
    virtual QString toDDL() const override;
    virtual ActionResult insertMe() override;
    virtual ActionResult updateMe() override;
};

#endif // FIREBIRDSEQUENCE_H
