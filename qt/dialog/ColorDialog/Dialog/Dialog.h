#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Dialog.h"

class Dialog : public QMainWindow
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::DialogClass ui;
};
