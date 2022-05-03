#include "abstractusercontext.h"
#include <QWidget>
#include <QVariant>

AbstractUserContext::AbstractUserContext(QObject *parent) : QObject(parent)
{

}

void FocusWidgetContext::setFocusedWidget(QWidget *widget)
{
    setProperty("focusedWidget", widget->objectName());
    emit contextChanged();
}
