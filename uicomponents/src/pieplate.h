#ifndef PIEPLATE_H
#define PIEPLATE_H

#include <QGraphicsObject>
class PieDelegateItem;

class PiePlate : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PiePlate(QGraphicsItem *parent);
    virtual ~PiePlate();

    void setModel(QList<qreal> model);
    void setModel(QList<QObject *> model);

    void setRadius(qreal radius);
    qreal radius() const;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void createPies(int count);
    QList<PieDelegateItem *> _pies;
    qreal _radius;
};

#endif // PIEPLATE_H
