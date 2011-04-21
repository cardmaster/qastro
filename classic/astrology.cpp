#include "astrology.h"
#include "planetfactory.h"

Astrology::Astrology()
	: mTimeLoc(),mPlanets( * PlanetFactory::instance() ), mHouses(), mAspects(), mSigns()
{
}

void Astrology::calc( const TimeLoc &tl )
{
	mTimeLoc = tl;
	calc();
}
void Astrology::calc( const TimeLoc *tl )
{
	mTimeLoc = *tl;
	calc();
}

void Astrology::calc()
{
	mPlanets.calc( mTimeLoc );
	mHouses.calc( mTimeLoc );
	mAspects.calc( mPlanets );
	emit update( this );
}

void Astrology::update( const TimeLoc &tl, const QString &name)
{
	mName = name;
	calc( tl );
}
