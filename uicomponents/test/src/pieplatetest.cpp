#include "pieplatetest.h"
#include "ui_pieplatetest.h"
#include "piedelegateitem.h"
#include "piemodel.h"
#include "pieplate.h"

#include <QDebug>
#include <QFileDialog>
static const int ModelsCount = 12;

PiePlateTest::PiePlateTest(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::PiePlateTest),
    _plate (new PiePlate)
{
    _ui->setupUi(this);
    _ui->graphWidget->addItem(_plate, QPointF(150, 150));

    qreal angleInc(30.0);
    for (int i = 0; i < ModelsCount; ++i) {
        PieModel *pm = new PieModel(this);
        pm->setStartAngle(i * angleInc);
        pm->setEndAngle((i + 1) * angleInc);
        if (! _models.isEmpty()) {
            connect (_models.last(), SIGNAL(endAngleChanged(qreal)), pm, SLOT(setStartAngle(qreal)) );
            connect (pm, SIGNAL(startAngleChanged(qreal)), _models.last(), SLOT(setEndAngle(qreal)) );
        }
        pm->setName(QString("#%1").arg(i));
        _models.append(pm);
    }
    if (_models.count() > 1) {
        connect (_models.last(), SIGNAL(endAngleChanged(qreal)), _models.first(), SLOT(setStartAngle(qreal)) );
        connect (_models.first(), SIGNAL(startAngleChanged(qreal)), _models.last(), SLOT(setEndAngle(qreal)) );
    }

    for (int i = 0; i < ModelsCount; ++i) {
        _numbers.append(i * angleInc);
    }

    setCurrentModel(_models.first());
    _ui->pieSelector->setMaximum(ModelsCount - 1);
    _ui->pieSelector->setValue(0);

    _plate->setModel(_numbers);
    _ui->radiusSpin->setValue(150);
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

void PiePlateTest::setCurrentModel(PieModel *pm)
{
    _model = pm;
    _ui->startAngleSlider->setValue(_model->startAngle());
    _ui->endAngleSlider->setValue(_model->endAngle());
}

void PiePlateTest::on_startAngleSlider_valueChanged(int val)
{
//    qDebug() << "Start Value: " << val;
    _model->setStartAngle(val);
}

void PiePlateTest::on_endAngleSlider_valueChanged(int val)
{
//    qDebug() << "End Value: " << val;
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
        _plate->setModel(_models);
        setCurrentModel(_models[_ui->pieSelector->value()]);
    } else {
        _plate->setModel(_numbers);
    }
}

void PiePlateTest::on_pieSelector_valueChanged(int value)
{
    setCurrentModel(_models[value]);
}

void piePlateTest()
{
    PiePlateTest *pt = new PiePlateTest;
    pt->show();
}

void PiePlateTest::on_ratioSpin_valueChanged(double ratio)
{
    qreal casted = static_cast<qreal>(ratio);
    _plate->setRadiusRatio(casted);
}

void PiePlateTest::on_radiusSpin_valueChanged(int radius)
{
    _plate->setRadius(radius);
}
