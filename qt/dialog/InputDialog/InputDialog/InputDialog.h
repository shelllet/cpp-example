#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_InputDialog.h"

class InputDialog : public QMainWindow
{
    Q_OBJECT

public:
    InputDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::InputDialogClass ui;
};
