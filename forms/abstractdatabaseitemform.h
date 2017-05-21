#ifndef ABSTRACTDATABASEITEMFORM_H
#define ABSTRACTDATABASEITEMFORM_H

#include <QDialog>
#include "qdbobjectitem.h"

class AbstractDatabaseEditForm : public QDialog
{
public:
    AbstractDatabaseEditForm(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    QDBObjectItem *objItem() const;
    void setObjItem(QDBObjectItem *objItem);

    virtual void objectToForm() = 0;
    virtual void formToObject() = 0;
protected:
    QDBObjectItem* _objItem;
};


#endif // ABSTRACTDATABASEITEMFORM_H
