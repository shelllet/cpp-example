#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TextBrower.h"

class TextBrower : public QMainWindow
{
    Q_OBJECT

public:
    TextBrower(QWidget *parent = Q_NULLPTR);

private:
    Ui::TextBrowerClass ui;
};
