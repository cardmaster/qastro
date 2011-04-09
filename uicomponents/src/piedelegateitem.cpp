#include "piedelegateitem.h"

#include <QPainter>
#include <cmath>

PieDelegateItem::PieDelegateItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    _radius(140.0),
    _startAngle(0),
    _endAngle(30)
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
