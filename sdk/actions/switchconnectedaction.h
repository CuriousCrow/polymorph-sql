#ifndef SWITCHCONNECTEDACTION_H
#define SWITCHCONNECTEDACTION_H

#include <QObject>
#include <core/basecontextaction.h>

class SwitchConnectedAction : public BaseItemPopupAction
{
  Q_OBJECT
public:
  Q_INVOKABLE SwitchConnectedAction();

  // BaseContextAction interface
public slots:
  virtual void doAction() override;

  // AbstractContextAction interface
protected slots:
  virtual void updateState() override;
private:
  bool isConnected();
};

#endif // SWITCHCONNECTEDACTION_H
