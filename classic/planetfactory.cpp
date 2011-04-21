#include <QStringList>
#include "planetfactory.h"
#include "planet.h"
#include "cswe.h"
PlanetFactory *PlanetFactory::mInstance = 0;
const PlanetFactory *PlanetFactory::instance()
{
	if( mInstance == 0 ){
		mInstance = new PlanetFactory();
	}
	return mInstance;
}

PlanetFactory::PlanetFactory()
	: mPlanetIds( )
{	
	mPlanetIds << Sun << Moon << Mercury << Venus << Mars << Jupiter << Saturn << Uranus << Neptune << Pluto;
}

Planet PlanetFactory::create( PlanetFactory::PlanetId id ) const
{
	return Planet( id );
}
