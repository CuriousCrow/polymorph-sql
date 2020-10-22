#include "sqlhelplookupprovider.h"
#include "../dbms/appconst.h"


SqlHelpLookupProvider::SqlHelpLookupProvider(QObject *parent) : QObject(parent)
{
  _helpModels.append(QKnowledgeBase::kb()->mKeywords);
  _helpModels.append(QKnowledgeBase::kb()->mFunctions);
}

QString SqlHelpLookupProvider::lookup(QString keyword)
{
  QString p1 = "<p>%1</p>";
  QString p2 = "<p align=\"right\"><a href=\"%1\"><small>See more..</small></a></p>";
  QString desc = "No data";
  QString link = "";

  int row = -1;
  foreach(LSqlTableModel* model, _helpModels) {
    row = model->rowByValue(F_NAME, keyword.toLower());
    if (row >= 0) {
      desc = model->data(row, F_DESCRIPTION).toString();
      link = model->data(row, F_DOC_LINK).toString();
    }
  }
  return p1.arg(desc) + (link.isEmpty() ? "" : p2.arg(link));
}
