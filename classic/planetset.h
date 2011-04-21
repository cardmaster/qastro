#ifndef PLANETSET_H
#define PLANETSET_H
#include <QStringList>
#include <QMap>
class PlanetFactory;
class Planet;
class TimeLoc;

class PlanetSet
{
public:
	PlanetSet( const PlanetFactory &pf );
	int countNabour( const Planet &t, double tolerance = 3.0 ) const;
	QStringList names() const;
	const QList<Planet> &planets() const{ return mPlanets; }
	const Planet &planet( const QString &name ) const;
	double eps() const{ return mEps; }
	void calc( const TimeLoc &tl );
	~PlanetSet();
private:
	QMap<QString, int> mMap;
	QList<Planet> mPlanets;
	double mEps;
};

#endif // PLANETSET_H
