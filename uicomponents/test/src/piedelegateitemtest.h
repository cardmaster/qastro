#ifndef PIEDELEGATEITEMTEST_H
#define PIEDELEGATEITEMTEST_H

#include <QWidget>

namespace Ui {
class PieDelegateItemTest;
}
class PieModel;
class PieDelegateItem;

class PieDelegateItemTest : public QWidget
{
    Q_OBJECT

public:
    explicit PieDelegateItemTest(QWidget *parent = 0);
    ~PieDelegateItemTest();
public slots:
    void on_startAngleSlider_valueChanged(int val);
    void on_endAngleSlider_valueChanged(int val);
    void on_nameEdit_textChanged(QString text);
    void on_imageSelector_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::PieDelegateItemTest *_ui;
    PieModel *_model;
    PieDelegateItem *_item;
};

#endif // PIEDELEGATEITEMTEST_H
