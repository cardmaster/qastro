#include "conf.h"
#include <QSettings>

Conf * Conf::mInstance(0);
const QString Conf::ImagePath("ImagePath");
const QString Conf::SwePath("SwePath");

Conf::Conf()
	: mSettings( new QSettings("./qastro.ini", QSettings::IniFormat) )
{
}
Conf::~Conf()
{
	mSettings->sync();
	delete mSettings;
	mSettings = 0;
	delete mInstance;
	mInstance = 0;
}

const QSettings *Conf::settings() const
{
	return mSettings;
}

QSettings *Conf::settings()
{
	return mSettings;
}

Conf * Conf::instance()
{
	if( mInstance == 0 ){
		mInstance = new Conf();
	}
	return mInstance;
}

void Conf::set( const QString &name, const QVariant &val )
{
	mSettings->setValue( name, val );
}

QVariant Conf::get( const QString &name, const QVariant &def  ) const
{
	return mSettings->value( name, def );
}

QString Conf::imagePath() const
{
	return get( ImagePath ).toString();
}

QString Conf::swePath() const
{
	return get( SwePath, QString(":/ephe") ).toString();
}

void Conf::load()
{
	mSettings->sync();
}

void Conf::save()
{
	mSettings->sync();
}

