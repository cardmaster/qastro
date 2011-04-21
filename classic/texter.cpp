#include <QString>
#include <QTextBrowser>
#include "texter.h"
#include "astrology.h"

Texter::Texter( QTextBrowser *ui, QObject *parent )
	: QObject( parent ), mUi(ui)
{
}

QString Texter::displayPlanet( const Planet &p, const Signs &s )
{
	QString text = QString("%1: %2").arg( p.name(), s.format(p.longitude()) );
	return text;
}

QString Texter::displayHouse( const Houses &h, const Signs &s  )
{
	QString text;
	for( int i = 1; i <= 12; ++i ){
		text.append( QString(tr("House%1: %2\n")).arg(i).arg(s.format(h.cusp(i)) ) );
	}
	return text;
}

QString Texter::displayAspect( const Aspect & a)
{
	QString typestr;
	switch( a.type() ){
	case Aspect::Conjunction:
		typestr = tr("Con");
		break;
	case Aspect::Opposition:
		typestr = tr("Opp");
		break;
	case Aspect::Sextile:
		typestr = tr("Sex");
		break;
	case Aspect::Trine:
		typestr = tr("Tri");
		break;
	case Aspect::Square:
		typestr = tr("Squ");
		break;
	default:
	case Aspect::None:
		return QString("");
	}
	return QString("%1 %2 %3(%4)").arg( a.start().name(), typestr, a.end().name() ).arg( a.diff() );
}

void Texter::display(const Astrology *astro)
{
	mUi->clear();
	QString name(astro->name());
	if( name.isEmpty() ){
		mUi->append( tr("<b>Thank you for Using</b>") );
	} else {
		mUi->append( QString( tr( "%1's Analysis" ) ).arg(name) );
	}
	if( ! astro->timeLoc().name().isEmpty() )
		mUi->append( QString( tr("From %2") ).arg(astro->timeLoc().name()) );
	mUi->append( tr("Lon: %1").arg( astro->timeLoc().longitude() ) );
	mUi->append( tr("Lat: %1").arg( astro->timeLoc().latitude() ));
	mUi->append( tr("Julian: %1").arg(astro->timeLoc().julianTime()) );


	mUi->append( tr("\nPlanets: ") );
	foreach( const Planet &pl, astro->planets().planets() ){
		mUi->append( displayPlanet(pl, astro->signs()) );
	}
	mUi->append( tr("\nHouses:") );
	mUi->append( displayHouse(astro->houses(), astro->signs()) );
	mUi->append( tr("Aspects:") );
	foreach( const Aspect &as, astro->aspects().aspects() ){
		mUi->append( displayAspect(as) );
	}
}
