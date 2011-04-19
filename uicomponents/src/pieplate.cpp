#include "pieplate.h"
#include "piedelegateitem.h"

#include <QPainter>

PiePlate::PiePlate(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
}

PiePlate::~PiePlate()
{
}


void PiePlate::setModel(QList<PieModel *> model)
{
    createPies(model.count());
    QList<PieModel *>::iterator it = model.begin();
    foreach (PieDelegateItem *pie, _pies) {
        pie->setModel(*it);
        ++it;
    }
}

void PiePlate::setModel(QList<QObject *> model)
{
    createPies(model.count());
    QList<QObject *>::iterator it = model.begin();
    foreach (PieDelegateItem *pie, _pies) {
        pie->setModel(*it);
        ++it;
    }
}

void PiePlate::setModel(QList<qreal> model)
{
    int cnt = model.count();
    createPies(cnt);
    foreach (PieDelegateItem *pie, _pies) {
        pie->detachModel();
    }

    qreal prev = model.first();
    _pies[0]->setStartAngle(prev);
    for (int i = 1; i < cnt; ++i) {
        qreal cur = model[i];
        _pies[i - 1]->setEndAngle(cur);
        _pies[i]->setStartAngle(cur);
        prev = cur;
    }
    _pies[cnt - 1]->setEndAngle(model.first());
}

void PiePlate::createPies(int count)
{
    while (_pies.count() > count) {
        delete _pies.last();
        _pies.removeLast();
    }
    while (_pies.count() < count) {
        PieDelegateItem *pie = new PieDelegateItem(this);
        pie->setPos(0, 0);
        _pies.append(pie);
    }
}

void PiePlate::setRadius(qreal radius)
{
    if (radius != _radius) {
        prepareGeometryChange();
        _radius = radius;
        foreach (PieDelegateItem *pie, _pies) {
            pie->setRadius(radius);
        }
    }
}

qreal PiePlate::radius() const
{
    return _radius;
}

QRectF PiePlate::boundingRect() const
{
    qreal rad = radius();
    return QRectF(-rad, -rad, rad, rad);
}

void PiePlate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawEllipse(boundingRect());
}
