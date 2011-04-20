#include "pieplate.h"
#include "piedelegateitem.h"

#include <QPainter>

PiePlate::PiePlate(QGraphicsItem *parent) :
    PlateItem(parent),
    _radiusRatio(1.0)
{
    connect (this, SIGNAL(radiusChanged(qreal)), this, SLOT(onRadiusChanged(qreal)));
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
        PieDelegateItem *pie = new PieDelegateItem(0, this);
        pie->setRadius(pieRadius());
        pie->setPos(0, 0);
        _pies.append(pie);
    }
}

void PiePlate::updatePieRadius()
{
    foreach (PieDelegateItem *pie, _pies) {
        pie->setRadius(pieRadius());
    }
}

void  PiePlate::setRadiusRatio(qreal ratio)
{
    if (_radiusRatio != ratio) {
        _radiusRatio = ratio;
        updatePieRadius();
    }
}

qreal  PiePlate::radiusRatio() const
{
    return _radiusRatio;
}

qreal PiePlate::pieRadius() const
{
    return radius() * radiusRatio();
}

void PiePlate::onRadiusChanged(qreal rad)
{
    updatePieRadius();
}
