#ifndef PIEDELEGATEITEM_H
#define PIEDELEGATEITEM_H

#include <QGraphicsObject>

class PieModel;
class QGraphicsTextItem;
class QGraphicsPixmapItem;

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
    Q_PROPERTY (qreal startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged);
    Q_PROPERTY (qreal endAngle READ endAngle WRITE setEndAngle NOTIFY endAngleChanged);
    Q_PROPERTY (QString name READ name WRITE setName);
    Q_PROPERTY (QString detail READ detail WRITE setDetail);
    Q_PROPERTY (QPixmap icon READ icon WRITE setIcon);

    explicit PieDelegateItem(QGraphicsItem *parent = 0);
    virtual ~PieDelegateItem();

    void setRadius(qreal rad);
    qreal radius() const;

    void setStartAngle(qreal angle);
    void setEndAngle(qreal angle);

    qreal startAngle() const;
    qreal endAngle() const;

    QString detail() const;
    QString name() const;
    QPixmap icon() const;

    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

/*! attach to a PieModel, change the view corresponding with model data
* \note dettach the model by passing in 0 (NULL pointer)
*/
    void setModel (PieModel *model);
    void detachModel();
/*! set a QObject * as model, if it could be qobject_cast to a PieModel, call
  The PieModel method. else, try to load data from properties
  */
    void setModel (QObject *model);
    QObject *model() const;

protected:
    virtual QPainterPath piePath() const;
    void updateView();

signals:
    void radiusChanged (qreal rad);
    void startAngleChanged (qreal sa);
    void endAngleChanged (qreal ea);

public slots:
    void onStartAngleChanged(qreal ang);
    void onEndAngleChanged(qreal ang);
    void setName(QString ang);
    void setDetail(QString det);
    void setIcon(QPixmap pix);

private:
    void positionItem(QGraphicsItem *item, qreal rate);
    void updatePositions();

private:
    qreal _radius;
    qreal _startAngle;
    qreal _endAngle;

    PieModel *_model;
    QGraphicsPixmapItem *_icon;
    QGraphicsTextItem *_name;
    QGraphicsTextItem *_detail;
};

#endif // PIEDELEGATEITEM_H