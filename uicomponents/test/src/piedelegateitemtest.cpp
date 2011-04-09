#include "piedelegateitemtest.h"
#include "ui_piedelegateitemtest.h"
#include "piedelegateitem.h"
#include "piemodel.h"

#include <QDebug>
#include <QFileDialog>

PieDelegateItemTest::PieDelegateItemTest(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::PieDelegateItemTest),
    _model (new PieModel(this)),
    _item (new PieDelegateItem)

{
    _ui->setupUi(this);
    _ui->graphWidget->addItem(_item, QPointF(150, 150));
    _model->setStartAngle(0);
    _model->setEndAngle(30);
    _item->setModel(_model);
#if 0
    connect (_ui->startAngleSlider, SIGNAL(valueChanged(int)),
             this, SLOT(on_startAngleSlider_valueChanged(int)) );
    connect (_ui->endValueSlider, SIGNAL(valueChanged(int)),
             this, SLOT(on_endAngleSlider_valueChanged(int)) );
#endif
}

PieDelegateItemTest::~PieDelegateItemTest()
{
    delete _ui;
}

void PieDelegateItemTest::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        _ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void PieDelegateItemTest::on_startAngleSlider_valueChanged(int val)
{
    qDebug() << "Start Value: " << val;
    _model->setStartAngle(val);
}

void PieDelegateItemTest::on_endAngleSlider_valueChanged(int val)
{
    qDebug() << "End Value: " << val;
    _model->setEndAngle(val);
}

void PieDelegateItemTest::on_nameEdit_textChanged(QString text)
{
    _model->setName(text);
}

void PieDelegateItemTest::on_imageSelector_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Your Icon Image"),
                        ".", tr("Image Files(*.png)") );
    if (filename.isEmpty())
        return;
    QPixmap pix(filename);
    if (! pix.isNull()) {
        _model->setIcon(pix);
    }
}

void pieDelegateItemTest()
{
    PieDelegateItemTest *pt = new PieDelegateItemTest;
    pt->show();
}
