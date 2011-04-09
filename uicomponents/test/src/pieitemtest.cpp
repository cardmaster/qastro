#include "piedelegateitem.h"
#include "graphwidget.h"

void pieDelegateItemTest()
{
    GraphWidget *grph = new GraphWidget;
    PieDelegateItem *pie = new PieDelegateItem;
    grph->addItem(pie);
    pie->setPos(150, 150);

    QGraphicsRectItem *iZone = new QGraphicsRectItem;
    iZone->setBrush(QBrush(QColor(200, 200, 0, 100)));
    iZone->setRect(0, 0, 300, 300);
    grph->addItem(iZone, QPointF(0, 0), -1);
    grph->show();
}
