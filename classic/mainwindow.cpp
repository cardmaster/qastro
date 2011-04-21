#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "astrology.h"
#include "astrologdat.h"
#include "texter.h"
#include "grapher.h"
#include "timeloceditor.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow),
	  astrology( new Astrology ), tloader( new AstrologDat ),
	  teditor(0), seditor( 0 )
{
	ui->setupUi(this);
	connect( ui->actionExit, SIGNAL(triggered()),
		 qApp, SLOT(quit()) );
	connect( ui->actionOpen, SIGNAL(triggered()),
		 this, SLOT(openChartFile()) );
	connect( ui->actionSave, SIGNAL(triggered()),
		 this, SLOT(saveChartFile()) );
	connect( ui->actionEditChart, SIGNAL(triggered()),
		 this, SLOT(editChart()) );
	texter = new Texter( ui->textDisplay );
	connect( astrology, SIGNAL(update(const Astrology*)),
		 texter, SLOT(display(const Astrology*)) );
	connect( astrology, SIGNAL(update(const Astrology*))
		 ,ui->graphDisplay,  SLOT(update( const Astrology*)));
	connect( ui->actionPreference, SIGNAL(triggered()),
		 this, SLOT(editPreference()) );
	astrology->calc();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete astrology;
	delete tloader;
	delete texter;
	if( teditor != 0 )
		delete teditor;
	if( seditor != 0 )
		delete seditor;
}

bool MainWindow::openChartFile()
{
	QString filename = QFileDialog::getOpenFileName();
	if( filename.isEmpty() )
		return false;
	if( ! tloader->load( filename ) )
		return false;
	astrology->setName( tloader->name() );
	astrology->calc( tloader->get() );
	return true;
}

bool MainWindow::saveChartFile()
{
	QString filename = QFileDialog::getSaveFileName();
	if( filename.isEmpty() )
		return false;
	tloader->set( astrology->timeLoc() );
	tloader->setName( astrology->name() );
	return tloader->save( filename );
}
void MainWindow::editChart()
{
	if( teditor == 0 ){
		teditor = new TimeLocEditor( this );
		connect( teditor, SIGNAL(update(TimeLoc,QString)),
			 astrology, SLOT(update(const TimeLoc&,const QString &)) );
	}
	teditor->edit( astrology->timeLoc(), astrology->name() );
}

void MainWindow::editPreference()
{
	if( seditor == 0 ){
		seditor = new SettingsEditor( this );
	}
	seditor->show();
	seditor->raise();
}

void MainWindow::newInfo( const TimeLoc &tl, const QString &name )
{
	astrology->setName( name );
	astrology->calc( tl );
}
