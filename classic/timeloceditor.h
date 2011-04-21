#ifndef TIMELOCEDITOR_H
#define TIMELOCEDITOR_H

#include <QDialog>

namespace Ui {
	class TimeLocEditor;
}
class TimeLoc;
class QString;
class TimeLocEditor : public QDialog {
	Q_OBJECT
public:
	TimeLocEditor(QWidget *parent = 0);
	~TimeLocEditor();
	void setName( const QString & );
	const QString & name() const;
	const TimeLoc & timeLoc() const;
	void setTimeLoc( const TimeLoc & );
public slots:
	void edit();
	void edit( const TimeLoc &tl, const QString &name = QString() );
	void editDone();
signals:
	void update( const TimeLoc &, const QString &);

protected:
	void changeEvent(QEvent *e);

private:
	Ui::TimeLocEditor *ui;
	TimeLoc *mTl;
	QString mName;
};

#endif // TIMELOCEDITOR_H
