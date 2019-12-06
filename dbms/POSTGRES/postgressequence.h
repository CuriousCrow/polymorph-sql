#ifndef POSTGRESSEQUENCE_H
#define POSTGRESSEQUENCE_H

#include <QObject>
#include "../dbsequenceitem.h"

class PostgresSequence : public DBSequenceItem
{
  Q_OBJECT
public:
  PostgresSequence(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // POSTGRESSEQUENCE_H
