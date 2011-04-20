#ifndef PLATEITEM_H
#define PLATEITEM_H
#include <QGraphicsItem>


class PlateItem : public QGraphicsObject
{
    Q_OBJECT
public:
    Q_PROPERTY (bool rotatable READ rotatable WRITE setRotatable NOTIFY rotatableChanged)
    Q_PROPERTY (qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY (QPixmap background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY (qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
public:
    explicit PlateItem(QGraphicsItem *parent = 0);

signals:
    void radiusChanged (qreal radius);
    void backgroundChanged (QPixmap background);
    void rotationChanged (qreal rotation);
    void rotatableChanged (bool rotatable);

public:
    void setRadius (qreal radius);
    qreal radius () const;

    void setBackground (const QPixmap & background);
    const QPixmap & background () const;

    void setRotation (qreal rotation);
    qreal rotation () const;

    void setRotatable (bool rotatable);
    bool rotatable () const;

public:
    QRectF boundingRect() const;
protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /*Mouse Events*/
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal _radius;
    QPixmap _background;
    qreal _rotation;
    bool _rotatable;

    QPointF _origPoint;
    qreal _curRotation;
};
#endif // PLATEITEM_H
