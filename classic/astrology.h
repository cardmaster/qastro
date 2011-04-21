#ifndef ASTROLOGY_H
#define ASTROLOGY_H
#include <QObject>
#include "planetset.h"
#include "houses.h"
#include "aspect.h"
#include "signs.h"
#include "timeloc.h"
class Astrology : public QObject
{
	Q_OBJECT
public:
	Astrology();
	const QString & name() const { return mName; }
	void setName( const QString &name )
	{
		mName = name;
		emit update(this);
	}
	const PlanetSet &planets() const { return mPlanets; }
	const Houses & houses() const { return mHouses; }
	const AspectSet & aspects() const { return mAspects; }
	const TimeLoc & timeLoc() const { return mTimeLoc; }
	const Signs &signs() const { return mSigns; }
signals:
	void update( const Astrology *astro );
public slots:
	void calc();
	void calc( const TimeLoc &tl );
	void calc( const TimeLoc *tl );
	void update( const TimeLoc &, const QString &);
private:
	QString mName;
	TimeLoc mTimeLoc;
	PlanetSet mPlanets;
	Houses mHouses;
	AspectSet mAspects;
	Signs mSigns;
};

#endif // ASTROLOGY_H
