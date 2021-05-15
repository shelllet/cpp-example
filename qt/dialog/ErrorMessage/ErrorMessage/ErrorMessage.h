#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ErrorMessage.h"

class ErrorMessage : public QMainWindow
{
    Q_OBJECT

public:
    ErrorMessage(QWidget *parent = Q_NULLPTR);

private:
    Ui::ErrorMessageClass ui;
};
