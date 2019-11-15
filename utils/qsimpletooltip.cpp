#include "qsimpletooltip.h"
#include <QStylePainter>
#include <QStyleOptionFrame>
#include <QEvent>
#include <QDebug>
#include <QKeyEvent>


QSimpleTooltip::QSimpleTooltip(QWidget *parent) : QLabel(parent, Qt::Popup)
{
    _showTimer = new QTimer(this);    
    connect(_showTimer, SIGNAL(timeout()), this, SLOT(hide()));
    setWordWrap(true);
    hide();
}

void QSimpleTooltip::popup(QString toolTip, QPoint globalPos)
{
    if (_secDuration > 0)
        _showTimer->start(_secDuration * 1000);
    QPoint relPos = mapToParent(mapFromGlobal(globalPos));
    if (_lookupProvider)
        setText(_lookupProvider->lookup(toolTip));
    else
        setText(toolTip);
    setMargin(_margin);
    setGeometry(relPos.x(), relPos.y(), sizeHint().width(), sizeHint().height());
    show();
}

void QSimpleTooltip::setWidget(QWidget *widget)
{
    widget->installEventFilter(this);
}

void QSimpleTooltip::setDuration(int sec)
{
    _secDuration = sec;
}

void QSimpleTooltip::setLookupProvider(HelpLookupProvider *provider)
{
    _lookupProvider = provider;
}

void QSimpleTooltip::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionFrame opt;
    opt.init(this);
    p.drawPrimitive(QStyle::PE_PanelTipLabel, opt);
    p.end();

    QLabel::paintEvent(event);
}

bool QSimpleTooltip::eventFilter(QObject *watched, QEvent *event)
{
  Q_UNUSED(watched)
  Q_UNUSED(event)
//    qDebug() << "event" << event->type();
    return false;
}

bool QSimpleTooltip::event(QEvent *event)
{
//    qDebug() << "event" << event->type();
    if (event->type() == QEvent::MouseButtonPress) {
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
