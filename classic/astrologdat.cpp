#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QStringList>
#include "astrologdat.h"
#include "timeloc.h"
#define QASTRO_DEBUG 1
#if QASTRO_DEBUG
#include <QDebug>
#endif

const QString AstrologDat::dtformat("M d yyyy H:mm:ss");

AstrologDat::AstrologDat()
	: mTl(), mName()
{
}

AstrologDat::AstrologDat( const QString &filename )
	: mTl(), mName()
{
	load(filename);
}

void AstrologDat::setName(const QString &name)
{
	mName = name;
}

QString AstrologDat::name() const
{
	return QString(mName);
}

const TimeLoc & AstrologDat::get() const
{
	return mTl;
}

void AstrologDat::set( const TimeLoc &ttl )
{
	mTl = ttl;
}
QString AstrologDat::formatDms( double val, QChar neg, QChar pos )
{
	double calc = val;
	int deg, min, sec;
	deg = static_cast<int>(calc);
	calc -= deg;
	calc *= 60;
	min = static_cast<int>(calc);
	calc -= min;
	calc *= 60;
	sec = static_cast<int>(calc);
	return QString( "%1:%2:%3" ).arg(deg).arg(min).arg(sec).append( (val >= 0) ? pos : neg );
}

double  AstrologDat::dmsDouble( const QString &str )
{
	QRegExp reg("(\\d+):?(\\d*):?(\\d*)");
	if( reg.indexIn( str ) >= 0 ){
		QStringList list = reg.capturedTexts();
		return list[1].toDouble() + list[2].toDouble()/60.0 + list[3].toDouble()/3600.0;
	}
	return 0;
}

QString AstrologDat::formatLon( double lon )
{
	return formatDms( lon, 'S', 'N' );
}

QString AstrologDat::formatLat( double lat )
{
	return formatDms( lat, 'W', 'E' );
}

bool AstrologDat::save()
{
	QFile file(mFileName);
	if( ! file.open(QIODevice::WriteOnly) ){
		return false;
	}
	QTextStream out( &file );

	out << "@0102  ; Astrolog32 chart info.\n\n"
	    << "; Date is in American format: month day year.\n\n";
	out << "/qb " << mTl.time().toString(dtformat) << " ST +0:00 ";
	out << formatLon(mTl.longitude()) << ' ' << formatLat(mTl.latitude()) << '\n';
	out << "/zi \"" << name() << "\" \"" << mTl.name() << "\" \n";

	out.flush();
	file.close();
	return true;
}

bool AstrologDat::save( const QString &filename )
{
	mFileName = filename;
	return save();

}

bool AstrologDat::load( const QString &filename )
{
	mFileName = filename;
	return load();
}

bool AstrologDat::setGeo( double val, char type )
{
	switch( type ){
	case 'w':
	case 'W':
		mTl.setLongitude( - val );
		break;
	case 'e':
	case 'E':
		mTl.setLongitude( val );
		break;
	case 'n':
	case 'N':
		mTl.setLatitude( val );
		break;
	case 's':
	case 'S':
		mTl.setLatitude( - val );
		break;
	default:
		return false;
	}
	return true;
}

bool AstrologDat::load()
{
	QFile file(mFileName);
	if( ! file.open(QIODevice::ReadOnly ) ){
		return false;
	}
	QTextStream in( &file );
	//                            m         d         y        h      m       s       ST+/- timezone                 deg  min  sec            deg    min  sec
	QRegExp qbexp( "\\s*/qb\\s*(\\d+)\\s+(\\d+)\\s+(\\d+)\\s+(\\d+):(\\d+):?(\\d*)\\s+ST\\s*([+-]\\d+):?(\\d+)\\s+(\\d+:?\\d*:?\\d*)(\\w)\\s+(\\d+:?\\d*:?\\d*)(\\w)" );
	QRegExp ziexp( "\\s*/zi\\s*\"(.*)\"\\s*\"(.*)\"");
	ziexp.setMinimal( true );
	bool hasQb( false ), hasZi( false );
	while( ! in.atEnd() ){
		QString line = in.readLine();
		if( (!hasQb) && ( qbexp.indexIn(line) >= 0 ) ){
			QStringList list = qbexp.capturedTexts();
			/* capture date time and timezone */
			QDate date( list[3].toInt(), list[1].toInt(), list[2].toInt() );
			QTime srctime( list[4].toInt(), list[5].toInt(), list[6].toInt(), 0 );
			QDateTime srcdt( date, srctime, Qt::UTC );
			mTl.setTime( srcdt.addSecs( list[7].toInt() * 3600 + list[8].toInt() * 60 )  );
			/* capture geology infomation */
			setGeo( dmsDouble( list[9] ),  list[10].at( 0 ).toAscii() );
			setGeo( dmsDouble( list[11] ), list[12].at( 0 ).toAscii() );
			hasQb = true;
		} else if( (!hasZi) && ( ziexp.indexIn(line) >= 0 ) ) {
			QStringList list = ziexp.capturedTexts();
			this->setName( list[1] );
			mTl.setName( list[2] );
			hasZi = true;
		}
		if( hasQb && hasZi )
			break;
	}
	file.close();
	return hasQb && hasZi;
}
