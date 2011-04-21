#include <QDateTime>
#include "timeloc.h"
#include "cswe.h"

TimeLoc::TimeLoc( const TimeLoc &src )
	: mName( src.name() ), mLatitude( src.latitude() ), mLongitude( src.longitude() ), mTime( src.time() )
{
}
TimeLoc::TimeLoc( double lon, double lat, const QDateTime &time )
	: mName(), mLatitude( lat ), mLongitude( lon ), mTime( time )
{
}
const TimeLoc & TimeLoc::operator= ( const TimeLoc &other )
{
	setName( other.name() );
	setLatitude( other.latitude() );
	setLongitude( other.longitude() );
	setTime( other.time() );
	return other;
}

void TimeLoc::setTime( const QDateTime &time )
{
	mTime = time;
}
void TimeLoc::setLatitude( double lat )
{
	mLatitude = lat;
}
void TimeLoc::setLongitude( double lon )
{
	mLongitude = lon;
}
static const double ClockDiv = 60.0;
double TimeLoc::julianTime() const
{
	QTime tm = time().time();
	QDate dt = time().date();
	double hours = tm.second();
	hours /= ClockDiv;
	hours += tm.minute();
	hours /= ClockDiv;
	hours += tm.hour();
	return swe_julday( dt.year(), dt.month(), dt.day(),
		       hours,
		       SE_GREG_CAL
		      );
}
