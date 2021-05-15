#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Line.h"

class Line : public QMainWindow
{
    Q_OBJECT

public:
    Line(QWidget *parent = Q_NULLPTR);

private:
    Ui::LineClass ui;
};
