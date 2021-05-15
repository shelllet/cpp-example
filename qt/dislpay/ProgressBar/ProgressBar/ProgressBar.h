#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProgressBar.h"

class ProgressBar : public QMainWindow
{
    Q_OBJECT

public:
    ProgressBar(QWidget *parent = Q_NULLPTR);

private:
    Ui::ProgressBarClass ui;
};
