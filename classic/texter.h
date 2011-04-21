#ifndef TEXTER_H
#define TEXTER_H
#include <QObject>
class QTextBrowser;
class QString;
class Astrology;
class Planet;
class Houses;
class Aspect;
class Signs;
class Texter:public QObject
{
	Q_OBJECT

public:
	Texter( QTextBrowser *ui, QObject *parent = 0 );
	QString displayPlanet( const Planet &p, const Signs &);
	QString displayHouse( const Houses &h, const Signs & );
	QString displayAspect( const Aspect & a);
public slots:
	void display( const Astrology * );

private:
	QTextBrowser *mUi;
};

#endif // TEXTER_H
