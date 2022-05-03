#include "extensions.h"


ExtensionPoint::ExtensionPoint(QString name, QString extensionClass, QString description, bool singleOnly):
  _name(name), _description(description), _extensionClass(extensionClass), _singleOnly(singleOnly)
{

}

QString ExtensionPoint::name() const
{
  return _name;
}

QString ExtensionPoint::description() const
{
  return _description;
}

QString ExtensionPoint::extensionClass() const
{
  return _extensionClass;
}

bool ExtensionPoint::singleOnly() const
{
  return _singleOnly;
}

bool ExtensionPoint::operator ==(const ExtensionPoint other)
{
  return (this->name() == other.name() && this->description() == other.description() &&
          this->extensionClass() == other.extensionClass() && this->singleOnly() == other.singleOnly());
}

Extensible::Extensible()
{
}

QSet<ExtensionPoint> Extensible::extensionPoints() const
{
  return _extensionPoints;
}
