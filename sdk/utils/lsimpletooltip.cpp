#include "lsimpletooltip.h"
#include <QStylePainter>
#include <QStyleOptionFrame>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>


LSimpleTooltip::LSimpleTooltip(QWidget *parent) : QLabel(parent, Qt::Popup)
{
  _showTimer = new QTimer(this);
  connect(_showTimer, SIGNAL(timeout()), this, SLOT(hide()));
  setWordWrap(true);
  hide();
}

void LSimpleTooltip::popup(QString keyword, QPoint globalPos)
{
  if (_secDuration > 0)
    _showTimer->start(_secDuration * 1000);
  QPoint relPos = mapToParent(mapFromGlobal(globalPos));
  if (_lookupProvider)
    setText(_lookupProvider->lookup(keyword));
  else
    setText(keyword);
  setMargin(_margin);
  setGeometry(relPos.x(), relPos.y(), sizeHint().width(), sizeHint().height());
  show();
}

void LSimpleTooltip::setWidget(QWidget *widget)
{
  widget->installEventFilter(this);
}

void LSimpleTooltip::setDuration(int sec)
{
  _secDuration = sec;
}

void LSimpleTooltip::setLookupProvider(HelpLookupProvider *provider)
{
  _lookupProvider = provider;
}

void LSimpleTooltip::paintEvent(QPaintEvent *event)
{
  QStylePainter p(this);
  QStyleOptionFrame opt;
  opt.initFrom(this);
  p.drawPrimitive(QStyle::PE_PanelTipLabel, opt);
  p.end();

  QLabel::paintEvent(event);
}

bool LSimpleTooltip::eventFilter(QObject *watched, QEvent *event)
{
  Q_UNUSED(watched)
  Q_UNUSED(event)
//  qDebug() << "Intercepted event:" << event->type();
  return false;
}

bool LSimpleTooltip::event(QEvent *event)
{
//  qDebug() << "Tooltip event:" << event->type();
  if (event->type() == QEvent::MouseButtonRelease) {
    if (isVisible()) {
      _showTimer->stop();
      hide();
    }
  }
  else if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    if (isVisible() && keyEvent->key() == Qt::Key_Escape) {
      _showTimer->stop();
      hide();
    }
  }
  return QLabel::event(event);
}

HelpLookupProvider::~HelpLookupProvider()
{
}
