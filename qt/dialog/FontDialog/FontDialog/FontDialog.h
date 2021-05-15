#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FontDialog.h"

class FontDialog : public QMainWindow
{
    Q_OBJECT

public:
    FontDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::FontDialogClass ui;
};
