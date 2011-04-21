#include "houses.h"
#include "planet.h"
#include "timeloc.h"
#include "cswe.h"
#include "astromath.h"
static const double ERR_ANG = -361.0;
Houses::Houses( int hsys )
	: mHsys( hsys )
{
}
Houses::Houses( const TimeLoc &tl, int hsys )
{
	calc( tl, hsys );
}

//return the cusp of house i
double Houses::cusp( int i ) const
{
	if( i >= 1 && i <= 12 )
		return mCusps[i];
	else
		return ERR_ANG;
}
//return the span of house i
double Houses::span( int i ) const
{
	int next = ( i >= 12 ) ? 1 : ( i + 1 );
	return format_a360( cusp( next ) - cusp( i ) );
}

double Houses::ascMc( int i ) const
{
	if( i >= 0 && i < 10 )
		return mAscMc[i];
	else
		return ERR_ANG;
}
double Houses::asc() const
{
	return ascMc( SE_ASC );
}
double Houses::des() const
{
	return format_a360( asc() + 180 );
}
double Houses::mc() const
{
	return ascMc( SE_MC );
}
double Houses::ic() const
{
	return format_a360( mc() + 180 );
}

//check which house the planet in
int Houses::judge( const Planet *p ) const
{
	int i;
	double ang = p->angle();
	for( i = 1; i <= 11; ++i ){
		if( ang > cusp(i) && ang < cusp(i + 1) )
			break;
	}
	return i;
}

void Houses::calc( const TimeLoc &tl, int hsys )
{
	mHsys = hsys;
	calc( tl );
}

void Houses::calc( const TimeLoc &tl )
{
	double tjd = tl.julianTime();
	swe_houses( tjd, tl.latitude(), tl.longitude(), mHsys, mCusps, mAscMc );
}

