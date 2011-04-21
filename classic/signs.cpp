#include "signs.h"
#include "cswe.h"
#include "planet.h"

Signs::Signs( )
	: mNames(QString("Unk"))
{
	mNames.append( "Ari" );
	mNames.append( "Tar" );
	mNames.append( "Gem" );

	mNames.append( "Can" );
	mNames.append( "Leo" );
	mNames.append( "Vir" );

	mNames.append( "Lib" );
	mNames.append( "Sco" );
	mNames.append( "Sag" );

	mNames.append( "Cap" );
	mNames.append( "Aqu" );
	mNames.append( "Pis" );
}

const QString & Signs::name( int i ) const
{
	if( i >= 1 && i <= 12 )
		return mNames[i];
	else
		return mNames[0];
}

QString Signs::format( double angle ) const
{
	int lonint = swe_csnorm( angle );
	return name( lonint / 30 + 1 );
}

