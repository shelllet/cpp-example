#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SpliterRubberBand.h"

class SpliterRubberBand : public QMainWindow
{
    Q_OBJECT

public:
    SpliterRubberBand(QWidget *parent = Q_NULLPTR);

private:
    Ui::SpliterRubberBandClass ui;
};
