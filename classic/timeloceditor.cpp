#include <QString>
#include "timeloceditor.h"
#include "ui_timeloceditor.h"
#include "timeloc.h"

TimeLocEditor::TimeLocEditor(QWidget *parent) :
		QDialog(parent),
		ui(new Ui::TimeLocEditor),
		mTl( new TimeLoc ),
		mName()
{
	ui->setupUi(this);
	connect( this, SIGNAL(accepted()),
		 this, SLOT(editDone()) );
}

TimeLocEditor::~TimeLocEditor()
{
	delete ui;
	delete mTl;
}

void TimeLocEditor::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void TimeLocEditor::edit()
{
	ui->iDateTime->setDateTime( mTl->time() );
	ui->iTimeZone->setValue( 0 );

	int deg,min,sec;
	/*setup the longitude input*/
	double lon = mTl->longitude();
	deg = static_cast<int>( lon );
	lon -= deg;
	lon *= 60;
	min = static_cast<int>( lon );
	lon -= min;
	lon *= 60;
	sec = static_cast<int>( lon );
	ui->iLonDeg->setValue( deg );
	ui->iLonMin->setValue( min );
	ui->iLonSec->setValue( sec );
	/*setup the latitude input*/
	double lat = mTl->latitude();
	deg = static_cast<int>( lat );
	lat -= deg;
	lat *= 60;
	min = static_cast<int>( lat );
	lat -= min;
	lat *= 60;
	sec = static_cast<int>( lat );
	ui->iLatDeg->setValue( deg );
	ui->iLatMin->setValue( min );
	ui->iLatSec->setValue( sec );

	/*setup the name & place input*/
	ui->iName->setText( mName );
	ui->iPlace->setText( mTl->name() );

	this->show();
}

void TimeLocEditor::edit( const TimeLoc &tl, const QString &name )
{
	*mTl = tl;
	if( !name.isEmpty() )
		mName = name;
	edit();
}
static double degsToDouble( int deg, int min, int sec )
{
	double ret(sec);
	ret /= 60.0;
	ret += min;
	ret /= 60.0;
	ret += deg;
	return ret;

}

void TimeLocEditor::editDone()
{
	mTl->setLatitude( degsToDouble( ui->iLatDeg->value(),
					ui->iLatMin->value(),
					ui->iLatSec->value()  ) );
	mTl->setLongitude( degsToDouble( ui->iLonDeg->value(),
					 ui->iLonMin->value(),
					 ui->iLonSec->value()  )  );
	mTl->setName( ui->iPlace->text() );
	QDateTime dt = ui->iDateTime->dateTime();
	int tz = ui->iTimeZone->value();
	mTl->setTime( dt.addSecs( - tz * 3600 ) );
	setName( ui->iName->text() );

	emit update( *mTl, mName );
}

void TimeLocEditor::setName( const QString &name )
{
	mName = name;
}

const QString & TimeLocEditor::name() const
{
	return mName;
}
const TimeLoc & TimeLocEditor::timeLoc() const
{
	return *mTl;
}
void TimeLocEditor::setTimeLoc( const TimeLoc &tl )
{
	*mTl = tl;
}
