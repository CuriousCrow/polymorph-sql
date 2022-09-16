#ifndef POSTGRESSEQUENCE_H
#define POSTGRESSEQUENCE_H

#include <QObject>
#include "objects/dbsequence.h"

/** PostgreSQL sequence item */
class PostgresSequence : public DBSequenceItem
{
  Q_OBJECT
public:
  Q_INVOKABLE PostgresSequence();

  // DBObjectItem interface
public:
  virtual bool refresh() Q_DECL_OVERRIDE;
};

#endif // POSTGRESSEQUENCE_H
