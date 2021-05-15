#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProgressDialog.h"

class ProgressDialog : public QMainWindow
{
    Q_OBJECT

public:
    ProgressDialog(QWidget *parent = Q_NULLPTR);

//slots:
//    void handleReportNumber(int);
private:
    Ui::ProgressDialogClass ui;
};
