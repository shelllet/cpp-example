#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MessageBox.h"

class MessageBox : public QMainWindow
{
    Q_OBJECT

public:
    MessageBox(QWidget *parent = Q_NULLPTR);

private:
    Ui::MessageBoxClass ui;
};
