#include "showsettingsformaction.h"
#include "forms/settingsform.h"

ShowSettingsFormAction::ShowSettingsFormAction() : BaseContextAction()
{
    setText("General");
}


void ShowSettingsFormAction::updateState()
{
    setEnabled(true);
    setVisible(true);
}

void ShowSettingsFormAction::doAction()
{
    QVariantHash p;
    SettingsForm* settingsForm = _core->dependency<SettingsForm>(p);
    if (settingsForm)
        settingsForm->show();
}

QStringList ShowSettingsFormAction::menuPath()
{
    QStringList pathList;
    pathList << "Settings";
    return pathList;
}


bool ShowSettingsFormAction::supportsExtensionPoint(const ExtensionPoint &extensionPoint) const
{
  return extensionPoint.name() == EP_MAINWINDOW_MAINMENU;
}
