#ifndef PIEDELEGATEITEM_H
#define PIEDELEGATEITEM_H

#include <QGraphicsObject>

class PieModel;
/*! Show a Pie based on A QObject's property
 * The pie delegate is base on a QObject's property as its model
 * Those property in the QObject will effects:
 * startAngle*, endAngle*, icon, name, discription (* is necessary)
 * if the model object doesn't have all the necessary props,
 * It'll fail to bind.
 */
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

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

/*! attach to a PieModel, change the view corresponding with model data
* \note dettach the model by passing in 0 (NULL pointer)
*/
    void setModel (PieModel *model);

protected:
    QPainterPath piePath() const;

signals:
    void radiusChanged (qreal rad);
    void startAngleChanged (qreal sa);
    void endAngleChanged (qreal ea);

private slots:
    void onModelPropertyChanged();

private:
    qreal _radius;
    qreal _startAngle;
    qreal _endAngle;

    PieModel *_model;

};

#endif // PIEDELEGATEITEM_H
