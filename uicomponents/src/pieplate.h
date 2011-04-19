#ifndef PIEPLATE_H
#define PIEPLATE_H

#include <QGraphicsObject>
class PieDelegateItem;
class PieModel;

class PiePlate : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PiePlate(QGraphicsItem *parent = 0);
    virtual ~PiePlate();

    void setModel(QList<qreal> model);
    void setModel(QList<QObject *> model);
    void setModel(QList<PieModel *> model);

    void setRadius(qreal radius);
    qreal radius() const;

    /*! Radius Ratio, the ratio between pie and plate */
    void setRadiusRatio(qreal ratio);
    qreal radiusRatio() const;
    qreal pieRadius() const;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void updatePieRadius();
    void createPies(int count);

private:
    QList<PieDelegateItem *> _pies;
    qreal _radius;
    qreal _radiusRatio;
};

#endif // PIEPLATE_H
