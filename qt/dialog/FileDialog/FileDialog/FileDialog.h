#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FileDialog.h"

class FileDialog : public QMainWindow
{
    Q_OBJECT

public:
    FileDialog(QWidget *parent = Q_NULLPTR);

private:
    Ui::FileDialogClass ui;
};
