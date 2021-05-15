#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Spinbox.h"

class Spinbox : public QMainWindow
{
    Q_OBJECT

public:
    Spinbox(QWidget *parent = Q_NULLPTR);

private:
    Ui::SpinboxClass ui;
};
