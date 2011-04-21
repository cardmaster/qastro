#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
	class Settings;
}

class SettingsEditor : public QDialog {
	Q_OBJECT
public:
	SettingsEditor(QWidget *parent = 0);
	~SettingsEditor();
public slots:
	void saveConfig();
protected:
	void changeEvent( QEvent *e );

private:
	Ui::Settings *ui;
};

#endif // SETTINGS_H
