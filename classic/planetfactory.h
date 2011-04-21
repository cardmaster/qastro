#ifndef PLANETFACTORY_H
#define PLANETFACTORY_H
#include <QList>
class Planet;
class PlanetFactory
{
public:
	enum PlanetId{
	    Sun = 0,
	    Moon,
	    Mercury,
	    Venus,
	    Mars,
	    Jupiter,
	    Saturn,
	    Uranus,
	    Neptune,
	    Pluto,
	};
	const QList<PlanetId> & planetIds() const{ return mPlanetIds; }
	Planet create( PlanetId id ) const;

	static const PlanetFactory *instance();
private:
	PlanetFactory();
	static PlanetFactory *mInstance;
	QList<PlanetId> mPlanetIds;
};

#endif // PLANETFACTORY_H
