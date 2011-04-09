#include "piedelegateitem.h"
#include "piemodel.h"
#include "graphwidget.h"

void pieDelegateItemTestSimple()
{
    GraphWidget *grph = new GraphWidget;
    PieDelegateItem *pie = new PieDelegateItem;
    grph->addItem(pie);
    pie->setPos(150, 150);

    PieModel *piem = new PieModel(grph);
    piem->setStartAngle(30);
    piem->setEndAngle(60);
    piem->setName(QString("NONONO<b>NO</b>"));
    pie->setModel(piem);
    piem->setName("Tarus");

    QGraphicsRectItem *iZone = new QGraphicsRectItem;
    iZone->setBrush(QBrush(QColor(200, 200, 0, 100)));
    iZone->setRect(0, 0, 300, 300);
    grph->addItem(iZone, QPointF(0, 0), -1);
    grph->show();
}
