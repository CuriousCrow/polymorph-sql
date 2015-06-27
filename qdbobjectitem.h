#ifndef QDBOBJECTITEM_H
#define QDBOBJECTITEM_H

#include "lstandardtreemodel.h"
#include <QSqlDatabase>

class QDBObjectItem : public LAbstractTreeItem
{
  Q_OBJECT
  Q_PROPERTY(QString caption READ caption WRITE setCaption)
public:
  enum ItemType {
    Database,
    Table,
    View,
    Sequence,
    Trigger,
    Procedure,
    Folder
  };

  QDBObjectItem(QString caption, QObject* parent = 0);
  ~QDBObjectItem();
  QString connectionName(){ return _connectionName; }

  virtual bool loadChildren() = 0;
  virtual QUrl objectUrl();
  virtual int type() = 0;
  virtual bool setData(int column, QVariant value, int role);

  virtual bool insertMe();
  virtual bool updateMe();
  virtual bool deleteMe();

  QString caption() const;
  void setCaption(const QString &caption);

  QStringList propertyList();
protected:
  QString _connectionName;
  QString _caption;
public slots:
  void updateObjectName();
};

#endif // QDBOBJECTITEM_H
