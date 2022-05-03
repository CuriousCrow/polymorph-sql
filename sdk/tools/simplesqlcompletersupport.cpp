#include "simplesqlcompletersupport.h"
#include "objects/appconst.h"
#include <QTableView>
#include <QHeaderView>

SimpleSqlCompleterSupport::SimpleSqlCompleterSupport(QObject *parent) : QObject(parent)
{

}

void SimpleSqlCompleterSupport::inject_kb_into_kb(LKnowledgeBase *kb)
{
  _kb = kb;
  _knowledgeModel = new JointDBOjbectModel(this);
  _knowledgeModel->registerColumn(F_NAME);
  _knowledgeModel->registerColumn(F_TYPE);
  _knowledgeModel->registerColumn(F_DESCRIPTION);
  _knowledgeModel->registerColumn(F_DOC_LINK);

  _objectsModel = new LDBObjectTableModel(this);
  _objectsModel->registerColumn(F_NAME);
  _objectsModel->registerColumn(F_TYPE);
  _objectsModel->registerColumn(F_DESCRIPTION);
  _objectsModel->registerColumn(F_DOC_LINK);
  _objectsModel->setFixedValue(F_DESCRIPTION, "");
  _objectsModel->setFixedValue(F_DOC_LINK, "");

  _completer = new LTextCompleter(_knowledgeModel, this);
  QTableView* completerView = new QTableView();
  completerView->horizontalHeader()->hide();
  completerView->verticalHeader()->hide();
  completerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  _completer->setPopup(completerView);
  _completer->setCaseSensitivity(Qt::CaseInsensitive);
  connect(_completer, &LTextCompleter::completerRequested,
          this, &SimpleSqlCompleterSupport::onCompleterRequested);
}

void SimpleSqlCompleterSupport::setWidget(QWidget *editor)
{
  _completer->setWidget(editor);
}

void SimpleSqlCompleterSupport::setDatabaseItem(DBDatabaseItem *dbItem)
{
  _dbItem = dbItem;
  _knowledgeModel->clear();
  _knowledgeModel->addModel(FOLDER_KEYWORDS, _kb->modelByType(OBJTYPE_KEYWORD, dbItem->driverName()));
  _knowledgeModel->addModel(FOLDER_FUNCTIONS, _kb->modelByType(OBJTYPE_FUNCTION, dbItem->driverName()));
  _objectsModel->setQuery(dbItem->getAllObjectListSql());
  _objectsModel->reload(dbItem->connectionName());
  _knowledgeModel->addModel(FOLDER_OBJECTS, _objectsModel);
}

void SimpleSqlCompleterSupport::setItem(DBObjectItem *objItem)
{
  DBDatabaseItem* dbItem = _ds->databaseItem(objItem);
  setDatabaseItem(dbItem);
}

LDBObjectTableModel *SimpleSqlCompleterSupport::objectsModel()
{
  return _objectsModel;
}

QString SimpleSqlCompleterSupport::aliasSource(const QString &alias) const
{

  QString aliasPattern = "(?:from|join)\\s+([A-Za-z_]+)\\s+%1\\b";
  QRegularExpression rx(aliasPattern.arg(alias));
  rx.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
  QPlainTextEdit* editor = static_cast<QPlainTextEdit*>(_completer->widget());
  QRegularExpressionMatch match = rx.match(editor->toPlainText());
  if (match.hasMatch()) {
    qDebug() << match.captured() << match.captured(1) << match.captured(2);
    return match.captured(1);
  }
  return alias;

}

void SimpleSqlCompleterSupport::onCompleterRequested(const QString &contextText)
{
  qDebug() << "Completer requested:" << contextText;
  if (contextText.contains(".")) {
    QString objName = contextText;
    objName = objName.section(".", 0, 0);
    objName = aliasSource(objName);

    QVariantMap dbObj = _objectsModel->rowByName(objName);
    if (!dbObj.isEmpty() && dbObj.value(F_TYPE).toString() == OBJTYPE_TABLE) {
      qDebug() << "Searching table:" << objName;
      DBObjectItem* item = _ds->itemByFolderAndName(_dbItem, FOLDER_TABLES, objName.toLower());
      if (item && item->type() == DBObjectItem::Table) {
        qDebug() << "Table object found";
        DBTableItem* tableItem = static_cast<DBTableItem*>(item);
        tableItem->reloadColumnsModel();
        _completer->setModel(tableItem->columnsModel());
        _completer->setMinCompletionPrefixLength(0);
        _completer->setCompletionColumn(1);
      }
    }
  }
  else {
    _completer->setModel(_knowledgeModel);
    _completer->setMinCompletionPrefixLength(1);
    _completer->setCompletionColumn(0);
  }
}
