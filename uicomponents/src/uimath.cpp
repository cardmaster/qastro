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

};
