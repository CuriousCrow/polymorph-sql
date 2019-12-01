#ifndef DBPOSTGRESEQUENCE_H
#define DBPOSTGRESEQUENCE_H

#include <QObject>
#include "../dbsequenceitem.h"

class DBPostgreSequence : public DBSequenceItem
{
  Q_OBJECT
public:
  DBPostgreSequence(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // DBPOSTGRESEQUENCE_H
