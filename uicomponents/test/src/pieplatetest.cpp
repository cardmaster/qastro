#include "pieplatetest.h"
#include "ui_pieplatetest.h"
#include "piedelegateitem.h"
#include "piemodel.h"

#include <QDebug>
#include <QFileDialog>

PiePlateTest::PiePlateTest(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::PiePlateTest),
    _model (new PieModel(this)),
    _item (new PieDelegateItem),
    _object (new QObject(this))

{
    _ui->setupUi(this);
    _ui->graphWidget->addItem(_item, QPointF(150, 150));
    _model->setStartAngle(0);
    _model->setEndAngle(30);
    _item->setModel(_model);
    _object->setProperty("startAngle", QVariant(-10.0));
    _object->setProperty("endAngle", QVariant(180.0));

#if 0
    connect (_ui->startAngleSlider, SIGNAL(valueChanged(int)),
             this, SLOT(on_startAngleSlider_valueChanged(int)) );
    connect (_ui->endValueSlider, SIGNAL(valueChanged(int)),
             this, SLOT(on_endAngleSlider_valueChanged(int)) );
#endif
}

PiePlateTest::~PiePlateTest()
{
    delete _ui;
}

void PiePlateTest::changeEvent(QEvent *e)
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

void PiePlateTest::on_startAngleSlider_valueChanged(int val)
{
    qDebug() << "Start Value: " << val;
    _model->setStartAngle(val);
}

void PiePlateTest::on_endAngleSlider_valueChanged(int val)
{
    qDebug() << "End Value: " << val;
    _model->setEndAngle(val);
}

void PiePlateTest::on_nameEdit_textChanged(QString text)
{
    _model->setName(text);
}

void PiePlateTest::on_imageSelector_clicked()
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

void PiePlateTest::on_modelSwitch_toggled(bool tog)
{
    if (tog) {
        _item->setModel(_model);
    } else {
        _item->setModel(_object);
    }
}

void piePlateTest()
{
    PiePlateTest *pt = new PiePlateTest;
    pt->show();
}
