#ifndef PIEMODEL_H
#define PIEMODEL_H
#include <QObject>


class PieModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY (QPixmap icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY (qreal startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged);
    Q_PROPERTY (qreal endAngle READ endAngle WRITE setStartAngle NOTIFY endAngleChanged);
    Q_PROPERTY (QString name READ name WRITE setStartAngle NOTIFY nameChanged);
    Q_PROPERTY (QString detail READ detail WRITE setStartAngle NOTIFY detailChanged);
public:
    explicit PieModel(QObject *parent = 0);
    virtual ~PieModel();
    void setStartAngle(qreal start);
    void setEndAngle(qreal end);
    void setName(const QString &nam);
    void setDetail(const QString &det);
    qreal startAngle() const;
    qreal endAngle() const;
    QString name() const;
    QString detail() const;

    void PieModel::setIcon (const QPixmap & icon);
    const QPixmap & PieModel::icon () const;




signals:
    void startAngleChanged(qreal ang);
    void endAngleChanged(qreal ang);
    void nameChanged(const QString &name);
    void detailChanged(const QString &disc);
    void iconChanged (const QPixmap & icon);

public slots:

private:
	qreal _startAngle;
	qreal _endAngle;
	QString _name;
	QString _detail;
    	QPixmap _icon;

};
#endif // PIEMODEL_H
