#ifndef LDATAWIDGETMAPPER_H
#define LDATAWIDGETMAPPER_H

#include <QDataWidgetMapper>

class LDataWidgetMapper : public QDataWidgetMapper
{
  Q_OBJECT
public:
  explicit LDataWidgetMapper(QObject *parent = nullptr);
  ~LDataWidgetMapper();
public slots:
  void updateReadOnlyWidgets(int row);
};

#endif // LDATAWIDGETMAPPER_H
