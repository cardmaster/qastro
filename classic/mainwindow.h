#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>

class TimeLoc;
class Astrology;
class DataFile;
class Grapher;
class Texter;
class TimeLocEditor;
class SettingsEditor;

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
/* connect the signal/slots here
 * i.e. connect astrology & displayer in the constructer
 */
	MainWindow(QWidget *parent = 0);
	~MainWindow();
public slots:
	bool saveChartFile();
	bool openChartFile();
	void editChart();
	void editPreference();
	void newInfo( const TimeLoc &tl, const QString &name );

private:
	Ui::MainWindow *ui;
	Astrology *astrology;
	DataFile *tloader;
	Texter *texter;
	TimeLocEditor *teditor;
	SettingsEditor *seditor;
};

#endif // MAINWINDOW_H
