#ifndef PIEPLATE_H
#define PIEPLATE_H
#include "plateitem.h"
#include <QPixmap>
class PieDelegateItem;
class PieModel;


class PiePlate : public PlateItem
{
    Q_OBJECT
/*! Properties */
public:
    Q_PROPERTY (QPixmap background READ background WRITE setBackground NOTIFY backgroundChanged)

public:
    explicit PiePlate(QGraphicsItem *parent = 0);
    virtual ~PiePlate();
    void setModel(QList<qreal> model);
    void setModel(QList<QObject *> model);
    void setModel(QList<PieModel *> model);

    /*! Radius Ratio, the ratio between pie and plate */
    void setRadiusRatio(qreal ratio);
    qreal radiusRatio() const;
    qreal pieRadius() const;

signals:
    void backgroundChanged (QPixmap background);

protected:
private slots:
    void onRadiusChanged(qreal rad);

private:
    void updatePieRadius();
    void createPies(int count);

private:
    QList<PieDelegateItem *> _pies;
    qreal _radiusRatio;
    QPixmap _background;

};
#endif // PIEPLATE_H
