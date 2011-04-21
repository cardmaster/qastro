#ifndef HOUSES_H
#define HOUSES_H
class TimeLoc;
class Planet;

class Houses
{
public:
	Houses( int hsys = 'P' );
	Houses( const TimeLoc &tl, int hsys = 'P' );
	int hsys() const{ return mHsys; }
	//return the cusp of house i
	double cusp( int i ) const;
	double span( int i ) const;
	double ascMc( int i ) const;
	double asc() const;
	double des() const;
	double mc() const;
	double ic() const;
	//check which house the planet in
	int judge( const Planet *p ) const;
	//calculate the cusps' positions
	virtual void calc( const TimeLoc &tl, int hsys );
	virtual void calc( const TimeLoc &tl );
protected:
	double mCusps[13];
	double mAscMc[10];
	int mHsys;
};




#endif // HOUSES_H
