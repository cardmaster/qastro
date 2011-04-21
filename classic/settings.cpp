#include "settings.h"
#include "ui_settings.h"
#include "conf.h"

SettingsEditor::SettingsEditor(QWidget *parent) :
		QDialog(parent),
		ui(new Ui::Settings)
{
	ui->setupUi(this);
	ui->swePath->setCaption( tr("Swe Path") );
	ui->imagePath->setCaption( tr("Image Path") );
	Conf *conf = Conf::instance();
	ui->swePath->setPath( conf->swePath() );
	ui->imagePath->setPath( conf->imagePath() );
	connect( this, SIGNAL(accepted()),
		 this, SLOT(saveConfig()) );
}

SettingsEditor::~SettingsEditor()
{
	delete ui;
}

void SettingsEditor::changeEvent(QEvent *e)
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

void SettingsEditor::saveConfig()
{
	Conf *conf = Conf::instance();
	conf->set( Conf::ImagePath, ui->imagePath->getPath() );
	conf->set( Conf::SwePath, ui->swePath->getPath() );
	conf->save();
}
