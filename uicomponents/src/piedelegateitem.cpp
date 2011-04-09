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

/*! Move this some where when u add new feature */
QPointF axisTransform (qreal rad, qreal pos, QSizeF itemsize = QSizeF(0, 0), QPointF startPoint = QPointF(0,0) );
static const qreal IconPosition = 0.8;
static const qreal NamePosition = 0.8;
static const qreal DetailPostion = 0.9;

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

#include <QTextDocument>
void PieDelegateItem::onNameChanged(QString name)
{
    if (_name == 0 && name.isEmpty())
        return;
    if (_name == 0) {
        _name = new QGraphicsTextItem(name, this);
    } else {
        _name->document()->setHtml(name);
    }
    positionItem(_name, NamePosition);
}

void PieDelegateItem::updatePositions()
{
    positionItem(_icon, IconPosition);
    positionItem(_name, NamePosition);
    positionItem(_detail, DetailPostion);
}

#include <QDebug>
void PieDelegateItem::positionItem(QGraphicsItem *item, qreal rate)
{
    if (item == 0)
        return;
    QPointF pos = axisTransform ( radius() * rate,
         (startAngle() + endAngle()) / 2.0,
         item->boundingRect().size()
    );
    qDebug() << "Postion " << item << " @ " << pos;
    item->setPos(pos);
}

void PieDelegateItem::onDetailChanged(QString det)
{
}

void PieDelegateItem::onIconChanged(QPixmap pix)
{
    if (pix.isNull() && _icon == 0)
        return;
    if (_icon == 0) {
        _icon = new QGraphicsPixmapItem(pix, this);
    } else {
        _icon->setPixmap(pix);
    }
    positionItem(_icon, 0.8);
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
    this->onStartAngleChanged(_model->startAngle());
    this->onEndAngleChanged(_model->endAngle());
    this->onIconChanged(_model->icon());
    this->onNameChanged(_model->name());
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

/*Angle Cacluations, I think they should be move to somewhere*/
static qreal angleToRad (qreal angle)
{
    return angle * M_PI / 180.0;
}

static qreal radToAngle (qreal rad)
{
    return rad * 180.0 / M_PI;
}

/*Calculate the position of a item with given radius and angle,
 * position it in the center
 * The angle is in degree, not rad degree
 */
QPointF axisTransform (qreal radius, qreal angle, QSizeF itemsize, QPointF startPoint)
{
    qreal rad = angleToRad(angle);
    qreal dx = cos(rad) * radius;
    qreal dy = - sin(rad) * radius; //Y axis going down in screen
    qreal xfix = itemsize.width() / 2.0;
    qreal yfix = itemsize.height() / 2.0;
    QPointF move(dx - xfix, dy - yfix);
    return startPoint + move;
}
