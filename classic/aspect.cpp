#include "aspect.h"
#include "planet.h"
#include "planetset.h"

double Aspect::mTolerance[] = { 6.0, 3.0, 5.0, 5.0 ,5.0, };
Aspect::Type Aspect::calc( const Planet &st, const Planet &ed )
{
	static const double aspects[] = { 0, 60, 90, 120, 180 };
	static const Type     types[] = { Conjunction, Sextile, Square, Trine, Opposition, None };
	static const int    NR_ASPECTS = sizeof( aspects ) / sizeof(double);

	double diff = qAbs<double>( st.longitude() - ed.longitude() );
	int i;
	for( i = 0; i < NR_ASPECTS; ++i ){
		if( qAbs<double>( diff - aspects[i] ) < mTolerance[i] )
			break;
	}
	return types[i];

}
double Aspect::diff() const
{
	return mStart->longitude() - mEnd->longitude();
}

Aspect::Aspect( const Planet &st, const Planet &ed )
	: mStart( &st ), mEnd( &ed )
{
	mType = calc( st, ed );
}

Aspect::Aspect( const Planet &st, const Planet &ed, Type type )
	: mStart( &st ), mEnd( &ed ), mType( type )
{
}


AspectSet::AspectSet()
	: mAspects()
{

}

AspectSet::AspectSet( const PlanetSet &ps )
	: mAspects()
{
	calc( ps );
}

AspectSet::AspectSet( const AspectSet &other )
	: mAspects( other.aspects() )
{

}

void AspectSet::calc( const PlanetSet &ps )
{
	mAspects.clear();
	const QList<Planet> pl( ps.planets() );
	for( QList<Planet>::const_iterator i = pl.constBegin(); i != pl.constEnd(); ++i ){
		for( QList<Planet>::const_iterator j = i + 1; j != pl.constEnd(); ++j ){
			Aspect::Type type;
			if( ( type = Aspect::calc( *i, *j ) ) != Aspect::None ){
				mAspects.append( Aspect( *i, *j, type ) );
			}
		}
	}
}
