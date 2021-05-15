#include "Slider.h"

Slider::Slider(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.horizontalSlider, &QSlider::valueChanged, [this](int value) {

        ui.lineEdit->setText(QString("%1").arg(value));
        
        });
}
