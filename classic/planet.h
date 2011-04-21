#ifndef PLANET_H
#define PLANET_H
#include <QString>
class PlanetFactory;
class TimeLoc;
class Planet
{
public:
	const QString &name() const{ return mName; }
	void setName( const QString &name );
	void calc( const TimeLoc &info );
	void calc( const TimeLoc &info, double eps );
	double latitude() const { return mLatitude; }
	double longitude() const { return mLongitude; }
	double angle() const{ return mAngle; }
private:
	friend class PlanetFactory;
	Planet( int id );
	Planet( int id, const QString & );
	Planet( int id, const char *sname );
        int mId;
	QString mName;
	double mLatitude, mLongitude, mAngle;
};

#endif // PLANET_H
