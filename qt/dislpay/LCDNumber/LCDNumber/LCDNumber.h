#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LCDNumber.h"

class LCDNumber : public QMainWindow
{
    Q_OBJECT

public:
    LCDNumber(QWidget *parent = Q_NULLPTR);

private:
    Ui::LCDNumberClass ui;
};
