#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Slider.h"

class Slider : public QMainWindow
{
    Q_OBJECT

public:
    Slider(QWidget *parent = Q_NULLPTR);

private:
    Ui::SliderClass ui;
};
