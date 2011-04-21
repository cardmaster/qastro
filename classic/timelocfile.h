#ifndef TIMELOCFILE_H
#define TIMELOCFILE_H
#include "timeloc.h"
class QString;
class DataFile{
public:
	virtual QString name() const = 0;
	virtual void setName( const QString & ) = 0;
	virtual const TimeLoc &get() const = 0;
	virtual void set( const TimeLoc & ) = 0;
	virtual bool save( const QString &filename ) = 0;
	virtual bool load( const QString &filename ) = 0;
};

#endif // TIMELOCFILE_H
