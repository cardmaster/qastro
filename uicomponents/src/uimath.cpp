#include "uimath.h"
#include <cmath>

namespace UIMath
{

qreal angleToRad(qreal angle)
{
    return angle * M_PI / 180.0;
}

qreal radToAngle(qreal rad)
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

TriAngleParam TriAngleParam::fromPoints(const QPointF &orig, const QPointF &dest)
{
    qreal x = orig.x();
    qreal y = orig.y();
    qreal cx = dest.x();
    qreal cy = dest.y();
    qreal dx = cx - x;
    qreal dy = cy - y;
    qreal sign = - dx * y + dy * x; // create a 正交 vector
    int sn = (sign > 0) ? 1 : -1;

    qreal vecmul = x * cx + y * cy;
    qreal lenmul = sqrt ((cx * cx + cy * cy) * (x * x + y * y));

    qreal cosa = vecmul / lenmul;
    qreal sina = sn * sqrt (1 - cosa * cosa);
    return TriAngleParam(sina, cosa);
}

TriAngleParam::TriAngleParam(qreal s, qreal c)
    : sine(s), cosi(c)
{
}


};
