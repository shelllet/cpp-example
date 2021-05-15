#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calendar.h"

class Calendar : public QMainWindow
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = Q_NULLPTR);

private:
    Ui::CalendarClass ui;
};
