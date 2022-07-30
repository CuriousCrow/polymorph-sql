#include "sqlhelplookupprovider.h"
#include "objects/appconst.h"


SqlHelpLookupProvider::SqlHelpLookupProvider(QObject *parent) : QObject(parent)
{
}

QString SqlHelpLookupProvider::lookup(QString keyword)
{
  QString p1 = "<p>%1</p>";
  QString p2 = "<p align=\"right\"><a href=\"%1\"><small>See more..</small></a></p>";
  QString desc = "No data";
  QString link = "";

  QVariantMap row;
  foreach(LDBObjectTableModel* model, _helpModels) {
    row = model->rowByName(keyword.toLower());
    if (!row.isEmpty()) {
      desc = row.value(F_DESCRIPTION).toString();
      link = row.value(F_DOC_LINK).toString();
      break;
    }
  }
  return p1.arg(desc) + (link.isEmpty() ? "" : p2.arg(link));
}

void SqlHelpLookupProvider::inject_by_kb(LKnowledgeBase *kb)
{
  _kb = kb;
}

void SqlHelpLookupProvider::updateHelpModels(QString driverName)
{
  _helpModels.clear();
  _helpModels.append(_kb->modelByType(OBJTYPE_KEYWORD, driverName));
  _helpModels.append(_kb->modelByType(OBJTYPE_FUNCTION, driverName));
}
