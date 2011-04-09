#ifndef PIEPLATE_H
#define PIEPLATE_H

#include <QGraphicsObject>

class PiePlate : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit PiePlate(QGraphicsItem *parent);
    virtual ~PiePlate();

signals:

public slots:

};

#endif // PIEPLATE_H
