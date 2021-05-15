#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_wizarddialog.h"

class wizarddialog : public QMainWindow
{
    Q_OBJECT

public:
    wizarddialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::wizarddialogClass ui;
};
