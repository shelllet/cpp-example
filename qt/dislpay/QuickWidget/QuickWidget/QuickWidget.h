#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QuickWidget.h"

class QuickWidget : public QMainWindow
{
    Q_OBJECT

public:
    QuickWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::QuickWidgetClass ui;
};
