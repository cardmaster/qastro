#ifndef UIMATH_H
#define UIMATH_H
#include <QPointF>
#include <QSizeF>
namespace UIMath
{

qreal angleToRad(qreal angle);
qreal radToAngle(qreal rad);
QPointF axisTransform (qreal rad, qreal pos, QSizeF itemsize = QSizeF(0, 0), QPointF startPoint = QPointF(0,0) );
class TriAngleParam {
public:
    /* caculate the triangle param between two different point */
    static TriAngleParam fromPoints(const QPointF &orig, const QPointF &dest);
public:
    TriAngleParam(qreal sin = 0, qreal cos = 1);
    TriAngleParam &operator = (const TriAngleParam &oth);
    qreal toAngle() const;
    qreal sine;
    qreal cosi;
};

};

#endif // UIMATH_H
