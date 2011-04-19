#ifndef PIEPLATETEST_H
#define PIEPLATETEST_H

#include <QWidget>

namespace Ui {
class PiePlateTest;
}
class PieModel;
class PieDelegateItem;

class PiePlateTest : public QWidget
{
    Q_OBJECT

public:
    explicit PiePlateTest(QWidget *parent = 0);
    ~PiePlateTest();
public slots:
    void on_startAngleSlider_valueChanged(int val);
    void on_endAngleSlider_valueChanged(int val);
    void on_nameEdit_textChanged(QString text);
    void on_imageSelector_clicked();
    void on_modelSwitch_toggled(bool tog);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PiePlateTest *_ui;
    PieModel *_model;
    PieDelegateItem *_item;
    QObject *_object;
};

#endif // PIEPLATETEST_H
