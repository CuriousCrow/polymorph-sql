#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <QObject>
#include <QSet>

#define EXTENSIBLE_CLASS "Extensible"
#define EXTENSION_CLASS "AbstractExtension"

class ExtensionPoint
{
public:
  ExtensionPoint(QString name, QString extensionClass, QString description, bool singleOnly);
  QString name() const;
  QString description() const;
  QString extensionClass() const;
  bool singleOnly() const;

  bool operator ==(const ExtensionPoint other);
private:
  QString _name;
  QString _description;
  QString _extensionClass;
  bool _singleOnly = false;
};

inline bool operator ==(const ExtensionPoint &extP1, const ExtensionPoint &extP2) {
  return (extP1.name() == extP2.name() && extP1.description() == extP2.description() &&
          extP1.extensionClass() == extP2.extensionClass() && extP1.singleOnly() == extP2.singleOnly());
}

inline uint qHash(const ExtensionPoint &key) {
  return qHash(key.name());
}

class AbstractExtension
{
public:
  virtual bool supportsExtensionPoint(const ExtensionPoint& extensionPoint) const = 0;
};


class Extensible
{
public:
  Extensible();

  virtual QSet<ExtensionPoint> extensionPoints() const;
  virtual void injectExtension(ExtensionPoint ep, QObject* e) = 0;
protected:
  QSet<ExtensionPoint> _extensionPoints;
};

#endif // EXTENSIONS_H
