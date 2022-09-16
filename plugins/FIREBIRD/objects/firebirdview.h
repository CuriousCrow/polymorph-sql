#ifndef FIREBIRDVIEW_H
#define FIREBIRDVIEW_H

#include "objects/dbview.h"
#include <QObject>

class FirebirdView : public DBViewItem
{
  Q_OBJECT
public:
  Q_INVOKABLE FirebirdView();

  // DBObjectItem interface
public:
  virtual bool refresh() override;
};

#endif // FIREBIRDVIEW_H
