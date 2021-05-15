#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GrapicsView.h"

class GrapicsView : public QMainWindow
{
    Q_OBJECT

public:
    GrapicsView(QWidget *parent = Q_NULLPTR);

private:
    Ui::GrapicsViewClass ui;
};
