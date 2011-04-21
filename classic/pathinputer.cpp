#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>

#include "pathinputer.h"

PathInputer::PathInputer( QWidget *parent, const QString &caption )
	: QWidget(parent), mCaption( caption )
{
	/* create items */
	text = new QLineEdit( this );
	button = new QPushButton( tr("..."), this );
	label = new QLabel( mCaption, this );
	dialog = 0;

	/* config layout */
	layout = new QHBoxLayout( this );
	layout->addWidget( label );
	layout->addWidget( text );
	layout->addWidget( button );
	this->setLayout( layout );

	/* edit slots */
	connect( button, SIGNAL(clicked()),
		 this, SLOT(selectPath()) );

}

void PathInputer::setCaption(const QString &caption)
{
	mCaption = caption;
	label->setText( mCaption );
	if( dialog != 0 ){
		dialog->setWindowTitle( mCaption );
	}
}

void PathInputer::setPath( const QString &path )
{
	text->setText( path );
	if( dialog != 0 )
		dialog->setDirectory( path );
}

QString PathInputer::caption() const
{
	return mCaption;
}

void PathInputer::selectPath( )
{
	if( dialog == 0 ){
		dialog = new QFileDialog( this, mCaption );
		dialog->setFileMode( QFileDialog::DirectoryOnly );
		dialog->setDirectory( text->text() );
		connect( dialog, SIGNAL(fileSelected(QString)),
			 text, SLOT( setText(QString) ) );
	}
	dialog->show();
}

PathInputer::~PathInputer()
{

}

QString PathInputer::getPath() const
{
	return text->text();
}
