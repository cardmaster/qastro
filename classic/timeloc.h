#ifndef TIMELOC_H
#define TIMELOC_H
#include <QDateTime>
class TimeLoc  
{
public:
	TimeLoc( const TimeLoc &src );
	TimeLoc( double lon = 0, double lat = 0, const QDateTime &time = QDateTime::currentDateTime() );
	const TimeLoc & operator = ( const TimeLoc &other );
	const QDateTime &time() const{ return mTime; }
	const QString &name() const { return mName; }
	double latitude() const{ return mLatitude; }
	double longitude() const{ return mLongitude; }
	double julianTime() const;
	void setTime( const QDateTime & );
	void setLatitude( double );
	void setLongitude( double );
	void setName( const QString & name ){ mName = name; }
private:
	QString mName;
	double mLatitude;
	double mLongitude;
	QDateTime mTime; 
};

#endif
