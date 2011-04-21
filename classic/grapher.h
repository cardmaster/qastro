#ifndef GRAPHER_H
#define GRAPHER_H

#include <QWidget>
class Astrology;
class Planet;
class Aspect;
class Houses;
class Signs;

class Grapher : public QWidget
{
	Q_OBJECT
public:
	explicit Grapher(QWidget *parent = 0);
	~Grapher();
	void updateRadius( const QSize & );
	QPointF calcPoint( double ang, double r );
	QPointF calcPlanetPos( double longitude );
	QColor signColor( int i );
	QColor houseColor( int i );
	QColor aspectColor( const Aspect & );
	QColor planetColor( const Planet & );
	void updateCenter( const QSize & );
	void paintSigns( QPainter &, const Signs & );
	void paintAspect( QPainter &, const Aspect & );
	void paintPlanet( QPainter &, const Planet &, double move = 0 );
	void paintHouses( QPainter &, const Houses & );
signals:

public slots:
	void update( const Astrology * );

protected:
	virtual void resizeEvent( QResizeEvent *event );
	virtual void paintEvent( QPaintEvent *event );

private:
	const Astrology *mAstro;
	QPointF mCenter;
	double mRadius;
	double pcRate;
	double sgRate;
	double hsRate;
};

#endif // GRAPHER_H
