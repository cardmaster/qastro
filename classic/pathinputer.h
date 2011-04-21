#ifndef PATHINPUTER_H
#define PATHINPUTER_H

#include <QWidget>
#include <QString>
class QFileDialog;
class QLineEdit;
class QPushButton;
class QHBoxLayout;
class QLabel;
class PathInputer : public QWidget
{
	Q_OBJECT
public:
	PathInputer( QWidget *parent, const QString &caption = tr("Select Path:") );
	~PathInputer();
	QString getPath() const;
	void setCaption( const QString & cpation );
	QString caption() const;
	void setPath( const QString & );

signals:
	void pathChanged( QString path );
public slots:
	void selectPath( );

private:
	QString mCaption;
	QLabel *label;
	QFileDialog *dialog;
	QLineEdit *text;
	QPushButton *button;
	QHBoxLayout *layout;
};

#endif // PATHINPUTER_H
