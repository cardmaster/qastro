#include "graphwidget.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>

void fanshapeTest()
{
    GraphWidget *grph = new GraphWidget;
    QGraphicsEllipseItem *fanshape = new QGraphicsEllipseItem;
    fanshape->setRect(10, 10, 280, 280);
    fanshape->setStartAngle(0 * 16);
    fanshape->setSpanAngle( - 180 * 16);
    grph->addItem(fanshape);
    QGraphicsRectItem *iZone = new QGraphicsRectItem;
    iZone->setBrush(QBrush(QColor(200, 200, 0, 100)));
    iZone->setRect(0, 0, 300, 300);
    grph->addItem(iZone, QPointF(0, 0), -1);
    grph->show();
}

