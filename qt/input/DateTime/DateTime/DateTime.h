#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DateTime.h"

class DateTime : public QMainWindow
{
    Q_OBJECT

public:
    DateTime(QWidget *parent = Q_NULLPTR);

private:
    Ui::DateTimeClass ui;
};
