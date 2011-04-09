#ifndef PIEDELEGATEITEM_H
#define PIEDELEGATEITEM_H

#include <QGraphicsObject>

class PieDelegateItem : public QGraphicsObject
{
    Q_OBJECT
public:
    Q_PROPERTY (qreal radius READ radius WRITE setRadius NOTIFY radiusChanged);
    Q_PROPERTY (qreal startAngle READ startAngle WRITE setRadius NOTIFY startAngleChanged);
    Q_PROPERTY (qreal endAngle READ endAngle WRITE setRadius NOTIFY endAngleChanged);

    explicit PieDelegateItem(QGraphicsItem *parent = 0);
    virtual ~PieDelegateItem();

    void setRadius(qreal rad);
    qreal radius() const;

    void setStartAngle(qreal angle);
    void setEndAngle(qreal angle);

    qreal startAngle() const;
    qreal endAngle() const;

    QRegion boundingRegion(const QTransform &itemToDeviceTransform) const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    QPainterPath piePath() const;

signals:
    void radiusChanged (qreal rad);
    void startAngleChanged (qreal sa);
    void endAngleChanged (qreal ea);

public slots:

private:
    qreal _radius;
    qreal _startAngle;
    qreal _endAngle;

};

#endif // PIEDELEGATEITEM_H
