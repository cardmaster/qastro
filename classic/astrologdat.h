#ifndef ASTROLOGDAT_H
#define ASTROLOGDAT_H
#include "timelocfile.h"

class AstrologDat : public DataFile
{
public:
	static const QString dtformat;
	static QString formatLon( double );
	static QString formatLat( double );
	static QString formatDms( double val, QChar neg, QChar pos );
	static double  dmsDouble( const QString &str );

public:
	AstrologDat();
	AstrologDat( const QString &fname );
	virtual void setName( const QString &name );
	virtual QString name() const;
	virtual bool save( const QString &filename );
	virtual bool load( const QString &filename );
	virtual const TimeLoc &get() const;
	virtual void set( const TimeLoc & );
	bool save();
	bool load();

private:
	bool setGeo( double val, char type );
	TimeLoc mTl;
	QString mName;
	QString mFileName;
};

#endif // ASTROLOGDAT_H
