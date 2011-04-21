#include <QString>
#include <QDebug>

#include "planet.h"
#include "timeloc.h"
#include "cswe.h"

Planet::Planet( int id, const char *sname )
		: mId(id), mName(sname)
{
}

Planet::Planet( int id, const QString &name )
		: mId(id), mName( name )
{
}
Planet::Planet( int id )
	: mId(id)
{
	char sname[20];
	swe_get_planet_name( id, sname );
	setName( QString(sname) );
}

void Planet::setName( const QString &name )
{
	mName = name;
}

void Planet::calc( const TimeLoc &info )
{
	/* calculate the eps */
	double x[6];
	char serr[ SZ_SERR ];
	double tjd = info.julianTime();
	tjd += swe_deltat( tjd );
	swe_calc( tjd, SE_ECL_NUT, 0, x, serr );
	/* than calc the position */
	calc( info, x[0] );
}

void Planet::calc( const TimeLoc &info, double eps )
{
	static const int IFLAG = SEFLG_SPEED | SEFLG_SWIEPH;
	double x[6];
	double transed[3];
	char serr[ SZ_SERR ];
	double tjd = info.julianTime();
	tjd += swe_deltat( tjd );
	swe_calc( tjd, mId, IFLAG, x, serr );
	mLongitude = x[0];
	mLatitude = x[1];
	swe_cotrans( x, transed, eps );
	mAngle = transed[0];
}
