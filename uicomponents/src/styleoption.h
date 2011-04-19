#ifndef STYLEOPTION_H
#define STYLEOPTION_H
#include <QObject>
#include <QBrush>
#include <QFont>
#include <QPen>

class StyleOption : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY (QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY (QPen pen READ pen WRITE setPen NOTIFY penChanged)
    Q_PROPERTY (QBrush brush READ brush WRITE setBrush NOTIFY brushChanged)

public:
    explicit StyleOption(QObject *parent = 0);
    void setBrush (const QBrush & brush);
    const QBrush & brush () const;
    void setPen (const QPen & pen);
    const QPen & pen () const;

    void setFont (const QFont & font);
    const QFont & font () const;

signals:
    void brushChanged (QBrush brush);
    void penChanged (QPen pen);
    void fontChanged (QFont font);

private: 
    QBrush _brush;
    QPen _pen;
    QFont _font;

};
#endif // STYLEOPTION_H
