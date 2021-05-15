#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLWidget.h"

class OpenGLWidget : public QMainWindow
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpenGLWidgetClass ui;
};
