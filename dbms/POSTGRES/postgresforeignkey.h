#ifndef POSTGRESFOREIGNKEY_H
#define POSTGRESFOREIGNKEY_H

#include <QObject>
#include "../dbforeignkey.h"

class PostgresForeignKey : public DBForeignKey
{
  Q_OBJECT
public:
  PostgresForeignKey(QString caption, QObject* parent = nullptr);

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // POSTGRESFOREIGNKEY_H
