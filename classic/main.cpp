#include <QtGui/QApplication>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>
#include "mainwindow.h"
#include "conf.h"
#include "cswe.h"
static void init_settings()
{
	Conf *conf = Conf::instance();
	QCoreApplication::setOrganizationName( "LeafJohnson" );
	QCoreApplication::setOrganizationDomain( "cheersounds.blogbus.com" );
	QCoreApplication::setApplicationName( "qastro" );
	QCoreApplication::setApplicationVersion( "0.1" );
	swe_set_ephe_path( conf->swePath().toAscii().data() );
}

int main(int argc, char *argv[])
{
	init_settings();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
