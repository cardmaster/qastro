#include "planetset.h"
#include "planetfactory.h"
#include "planet.h"
#include "timeloc.h"
#include "cswe.h"

#include <QDebug>

PlanetSet::PlanetSet( const PlanetFactory &pf )
{
	foreach( PlanetFactory::PlanetId i, pf.planetIds() ){
		Planet p = pf.create( i );
		mMap.insert( p.name(), mPlanets.count() );
		mPlanets.append( p );
	}
}

QStringList PlanetSet::names() const
{
	return QStringList(mMap.keys());
}

const Planet &PlanetSet::planet( const QString &name ) const
{
	return mPlanets[ mMap.value( name ) ];
}

void PlanetSet::calc( const TimeLoc &tl )
{
	double x[6];
	char serr[SZ_SERR];
	swe_calc_ut( tl.julianTime(), SE_ECL_NUT, 0, x, serr );
	mEps = x[0];
	qDebug() << "Before loop" << mPlanets.count() << "planets";
	for( int i = 0; i < mPlanets.size(); ++i ){
		Planet &pref = mPlanets[i];
		pref.calc( tl, mEps );
	}
}

int PlanetSet::countNabour( const Planet &t, double tolerance ) const
{
	int nNab(0);
	foreach( const Planet &p, this->mPlanets ){
		if( p.name() == t.name() )
			break;
		if( qAbs<double>( p.longitude() - t.longitude() ) < tolerance )
			++nNab;
	}
	return nNab;
}

PlanetSet::~PlanetSet()
{

}

