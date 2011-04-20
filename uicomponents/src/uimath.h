#ifndef UIMATH_H
#define UIMATH_H
#include <QPointF>
#include <QSizeF>
namespace UIMath
{

qreal angleToRad(qreal angle);
qreal radToAngle(qreal rad);
QPointF axisTransform (qreal rad, qreal pos, QSizeF itemsize = QSizeF(0, 0), QPointF startPoint = QPointF(0,0) );

};

#endif // UIMATH_H
