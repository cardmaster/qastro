#ifndef CONF_H
#define CONF_H
#include <QString>
#include <QVariant>
class QSettings;
class Conf
{
public:
	static const QString ImagePath;
	static const QString SwePath;
	static Conf * instance();
	~Conf();
	void load();
	void save();
	QSettings *settings();
	const QSettings *settings() const;
	QString imagePath() const;
	QString swePath() const;
	QVariant get( const QString &, const QVariant &def = QVariant() ) const;
	void set( const QString &key, const QVariant &val );

private:
	static Conf *mInstance;
	Conf();
	QSettings *mSettings;
};

#endif // CONF_H
