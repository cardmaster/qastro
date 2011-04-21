#ifndef PHASE_H
#define PHASE_H
#include "planet.h"
class Aspect
{
public:
	enum Type{
		None = 0,
		Conjunction = 1,
		Sextile = 2,
		Square = 3,
		Trine = 4,
		Opposition = 5,
	};

	static Aspect::Type calc( const Planet &st, const Planet &ed );
	Aspect( const Planet &st, const Planet &ed );
	Aspect( const Planet &st, const Planet &ed, Type type );

	Aspect::Type type() const{ return mType; }
	const Planet &start() const{ return *mStart; }
	const Planet &end() const{ return *mEnd; }
	double diff() const;

private:
	static double mTolerance[6];
	const Planet *mStart, *mEnd;
	Type mType;

};

#include <QList>
class PlanetSet;
class AspectSet
{
public:
	AspectSet();
	AspectSet( const PlanetSet &ps );
	AspectSet( const AspectSet &other );
	const QList<Aspect> &aspects() const{ return mAspects; }
	void calc( const PlanetSet &ps );
private:
	QList< Aspect > mAspects;

};
#endif // PHASE_H
