#include <QResizeEvent>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <cmath>
#include "grapher.h"
#include "astrology.h"
#include "astromath.h"
#define QASTRO_DEBUG 0
#if QASTRO_DEBUG
#include <QDebug>
#endif
using namespace std;

Grapher::Grapher(QWidget *parent) :
		QWidget(parent), mAstro(0), pcRate(0.75), sgRate( 0.86 ), hsRate( 0.85 )
{
	QWidget::setAutoFillBackground( true );
}
Grapher::~Grapher()
{
}

void Grapher::update( const Astrology *a )
{
	mAstro = a;
	QWidget::update();
}

void Grapher::resizeEvent( QResizeEvent *event )
{
	updateRadius( event->size() );
	updateCenter( event->size() );
	QWidget::update();
}

void Grapher::paintEvent( QPaintEvent *event )
{
	if( mAstro == 0 )
		return;
	updateRadius( size() );
	updateCenter( size() );
	QPainter p( this );
	QPen pen;
	pen.setWidth( 2 );
	p.setPen( pen );
	p.setRenderHint( QPainter::Antialiasing, true );
	paintSigns( p, mAstro->signs() );
	paintHouses( p, mAstro->houses() );
	foreach( const Aspect &as, mAstro->aspects().aspects() ){
		paintAspect( p, as );
	}

	foreach( const Planet &pl, mAstro->planets().planets() ){
		paintPlanet( p, pl, 40.0 *( mAstro->planets().countNabour( pl ) )  );
	}
	p.end();
}


void Grapher::updateRadius( const QSize &sz )
{
	double r = qMin( sz.width(), sz.height() );
	r *= 0.97;
	r /= 2.0;
	mRadius = r;
}
void Grapher::updateCenter(const QSize &size)
{
	mCenter = QPointF( size.width()/2.0, size.height()/2.0 );
}

QPointF Grapher::calcPlanetPos( double longitude )
{
	return calcPoint( longitude, mRadius*pcRate );
}
QPointF Grapher::calcPoint( double ang, double r )
{
	QPointF pos;
	double arc = angle_arc( ang );
	pos.setX( mCenter.x() + cos(arc) * r );
	pos.setY( mCenter.y() - sin(arc) * r );
	return pos;
}

QColor Grapher::signColor( int i )
{
	QColor ret = qRgb( 0, 0, 0 );
	switch( ( i - 1 ) % 4 ){
	case 0:
		ret = qRgb( 200, 100, 100 );
		break;
	case 1:
		ret = qRgb( 200, 200, 100 );
		break;
	case 2:
		ret = qRgb( 100, 200, 160 );
		break;
	case 3:
		ret = qRgb( 100, 130, 200 );
		break;
	}
	return ret;
}

QColor Grapher::houseColor( int i )
{
	QColor ret = qRgb( 0, 0, 0 );
	switch( ( i - 1 ) % 4 ){
	case 0:
		ret = qRgb( 255, 150, 150 );
		break;
	case 1:
		ret = qRgb( 255, 255, 150 );
		break;
	case 2:
		ret = qRgb( 150, 255, 214 );
		break;
	case 3:
		ret = qRgb( 150, 182, 255 );
		break;
	}
	return ret;
}

QColor Grapher::aspectColor( const Aspect &as )
{
	switch( as.type() ){
	case Aspect::None:
		return qRgb( 255, 255, 255 );
	case Aspect::Conjunction:
		return qRgb( 0, 127, 0 );
	case Aspect::Opposition:
		return qRgb( 0, 0, 255 );
	case Aspect::Square:
		return qRgb( 255, 0, 0 );
	case Aspect::Sextile:
		return qRgb( 0, 255, 0 );
	case Aspect::Trine:
		return qRgb( 0, 255, 127 );
	}
	return qRgb( 0, 0, 0 );
}

QColor Grapher::planetColor( const Planet &pl )
{
	return qRgb( 0, 0, 0 );
}

void Grapher::paintSigns( QPainter &p, const Signs &sg )
{
	double d = mRadius * 2.0;
	QRectF bigang( mCenter.x() - mRadius, mCenter.y() - mRadius, d, d );
	double r = mRadius * sgRate;
	QRectF smallang( mCenter.x() - r, mCenter.y() - r, d * sgRate, d * sgRate );
	QBrush brush( Qt::SolidPattern );
	for( int i = 1; i <= 12; ++i ){
		brush.setColor( signColor(i) );
		p.setBrush( brush );
		p.drawPie( bigang, ( i - 1 ) * 30 * 16, 30 * 16 );
		p.drawText( calcPoint( ( i - 1 ) * 30.0 + 15.0, mRadius ),
			    sg.name(i) );
	}
	p.setBrush( Qt::NoBrush );
	p.drawEllipse( bigang );
	p.drawEllipse( smallang );
}

void Grapher::paintAspect( QPainter &p, const Aspect &as )
{
	p.setPen( aspectColor(as) );
	p.drawLine( calcPlanetPos( as.start().longitude() ),
		    calcPlanetPos( as.end().longitude() ) );
}

void Grapher::paintPlanet( QPainter &p, const Planet &pl, double move )
{
	double r = mRadius * pcRate;
	QPointF pos( calcPoint( pl.longitude(), r - move) );
	QPen pen( planetColor(pl) );
	if( move > 0.5 || move < -0.5 ){
		pen.setStyle( Qt::DotLine );
		p.setPen( pen );
		p.drawLine( calcPoint( pl.longitude(), r ), pos );
	}
	pen.setStyle( Qt::SolidLine );
	p.setPen( pen );
	p.drawEllipse( pos, 5, 5 );
	p.drawText( pos, pl.name() );
}

void Grapher::paintHouses( QPainter &p, const Houses &hs )
{
	double r = mRadius * hsRate;
	double d = r * 2.0;
	QBrush brushbak( p.brush() );
	QBrush brush( Qt::SolidPattern );
	QRectF rectang( mCenter.x() - r, mCenter.y() - r, d, d );
	p.setPen( Qt::NoPen );
	for( int i = 1; i <= 12; ++i ){
		QColor color( houseColor(i) );
		brush.setColor(color );
		p.setBrush( brush );
		int end = ( i >= 12 ) ? 1 : (i + 1);
		double st = hs.cusp(i);
		double ed = format_a360( hs.cusp(end) - st );
#if QASTRO_DEBUG
		qDebug() << "st " << st <<" ed "<<ed;
		qDebug() << "st " << static_cast<int>( st * 16.0 ) << " ed " << static_cast<int>( ed * 16.0 ) << '\n';
#endif
		p.drawPie( rectang,
			   static_cast<int>( st * 16.0 ),
			   static_cast<int>( ed * 16.0 )
			 );
	}

	QPen pen( Qt::SolidLine );
	p.setPen( pen );
	for( int i = 1; i <= 12; ++i ){
		p.drawText( calcPoint(
				format_a360( hs.cusp(i) + hs.span( i ) / 2.0 ),
				r * 0.3 ),
			    QString("%1").arg( i ) );
	}
	pen.setWidth( 2 );
	QColor asc( qRgb( 255, 0, 0 ) );
	QColor des( qRgb( 0, 0, 0 ) );
	QColor mc( qRgb( 200, 200, 0 ) );
	QColor ic( qRgb( 0, 0, 100 ) );
	pen.setColor( asc );
	p.setPen( pen );
	p.drawLine( mCenter, calcPoint( hs.asc(), mRadius * 1.2 ) );
	pen.setColor( des );
	p.setPen( pen );
	p.drawLine( mCenter, calcPoint( hs.des(), mRadius * 1.2 ) );
	pen.setColor( mc );
	p.setPen( pen );
	p.drawLine( mCenter, calcPoint( hs.mc(), mRadius * 1.2 ) );
	pen.setColor( ic );
	p.setPen( pen );
	p.drawLine( mCenter, calcPoint( hs.ic(), mRadius * 1.2 ) );

	p.setBrush( brushbak );
}
