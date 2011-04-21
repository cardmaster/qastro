#ifndef SIGNS_H
#define SIGNS_H
#include <QStringList>
class Planet;
class Signs
{
public:
	Signs();
	const QString & name( int i ) const;
	QString format( double longitude ) const;
private:
	QStringList mNames;
};

#endif // SIGNS_H
