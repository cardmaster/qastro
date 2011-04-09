#include "piedelegateitem.h"
#include "piemodel.h"

#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <cmath>
/*! You have to make sure these 2 arrays match */
static const char * myslots[] = {
	SLOT(onDetailChanged(QString)),
	SLOT(onEndAngleChanged(qreal)),
	SLOT(onIconChanged(QPixmap)),
	SLOT(onNameChanged(QString)),
	SLOT(onStartAngleChanged(qreal))
};
static const char * mysignals[] = {
	SIGNAL(detailChanged(QString)),
	SIGNAL(endAngleChanged(qreal)),
	SIGNAL(iconChanged(QPixmap)),
	SIGNAL(nameChanged(QString)),
	SIGNAL(startAngleChanged(qreal)),
};
static const int SignalSlotsCount = sizeof(myslots) / sizeof(myslots[0]);

PieDelegateItem::PieDelegateItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    _radius(140.0),
    _startAngle(0),
    _endAngle(30),
    _model(0),
    _icon(0),
    _name(0),
    _detail(0)
{
}

PieDelegateItem::~PieDelegateItem()
{
}

//! if the pie is a circle, it'll be the bounding rect
QRectF PieDelegateItem::boundingRect() const
{
    qreal r = radius();
    qreal d = r * 2;
    return QRectF(-r, -r, d, d);
}

QPainterPath PieDelegateItem::shape() const
{
    return piePath();
}

QPainterPath PieDelegateItem::piePath() const
{
    QPainterPath path;
    path.arcTo(boundingRect(), _startAngle, _endAngle - _startAngle);
    path.lineTo(0, 0);
    return path;
}

void PieDelegateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Center at pos 0, 0
    QPainterPath pie = piePath();
    painter->setPen(QPen(QBrush(Qt::black), 2));
    painter->setBrush(QBrush(Qt::red));
    painter->drawPath(pie);
}

void PieDelegateItem::onStartAngleChanged(qreal ang)
{
    setStartAngle(ang);
}

void PieDelegateItem::onEndAngleChanged(qreal ang)
{
    setEndAngle(ang);
}

void PieDelegateItem::onNameChanged(QString ang)
{
}

void PieDelegateItem::onDetailChanged(QString det)
{
}

void PieDelegateItem::onIconChanged(QPixmap pix)
{
    if (pix.isNull() && _icon == 0)
        return;
    if (_icon == 0) {
        _icon = new QGraphicsPixmapItem(this);
    }
    _icon->setPixmap(pix);
}

void PieDelegateItem::setModel(PieModel *model)
{
    if (model != _model) {
        if (_model != 0) {
            detachModel();
        }
        _model = model;
        for (int i = 0; i < SignalSlotsCount; ++i) {
            connect (model, mysignals[i], this, myslots[i]);
        }
        updateView();
    }
}

void PieDelegateItem::detachModel()
{
    if (_model == 0)
        return;
    for (int i = 0; i < SignalSlotsCount; ++i) {
        disconnect(this, myslots[i]);
    }
}

void PieDelegateItem::updateView()
{
    if (_model == 0) { /*disctruct all accessory if no model */
        delete _name;
        delete _detail;
        delete _icon;
        return;
    }
    this->onNameChanged(_model->name());
    this->onIconChanged(_model->icon());
    this->onDetailChanged(_model->detail());
}

void PieDelegateItem::setRadius(qreal rad)
{
    if (_radius != rad) {
        prepareGeometryChange();
        _radius = rad;
        emit radiusChanged(rad);
    }
}

void PieDelegateItem::setStartAngle(qreal angle)
{
    if (_startAngle != angle) {
        _startAngle = angle;
        emit startAngleChanged(angle);
    }
}

void PieDelegateItem::setEndAngle(qreal angle)
{
    if (_endAngle != angle) {
        _endAngle = angle;
        emit endAngleChanged(angle);
    }
}

qreal PieDelegateItem::radius() const
{
    return _radius;
}

qreal PieDelegateItem::startAngle() const
{
    return _startAngle;
}

qreal PieDelegateItem::endAngle() const
{
    return _endAngle;
}
