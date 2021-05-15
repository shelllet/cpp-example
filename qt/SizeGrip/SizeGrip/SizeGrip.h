#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SizeGrip.h"

class SizeGrip : public QMainWindow
{
    Q_OBJECT

public:
    SizeGrip(QWidget *parent = Q_NULLPTR);

private:
    Ui::SizeGripClass ui;
};
