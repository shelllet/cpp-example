#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_co_stateChanged(int arg1)
{
    ui->checkBox_chi->blockSignals(true);
    ui->checkBox_eng->blockSignals(true);
    ui->checkBox_jp->blockSignals(true);

    ui->checkBox_chi->setChecked(arg1 == Qt::Checked);
    ui->checkBox_eng->setChecked(arg1 == Qt::Checked);
    ui->checkBox_jp->setChecked(arg1 == Qt::Checked);

    ui->checkBox_chi->blockSignals(false);
    ui->checkBox_eng->blockSignals(false);
    ui->checkBox_jp->blockSignals(false);
}

void MainWindow::on_checkBox_chi_stateChanged(int arg1)
{
    Qt::CheckState state;

    if (arg1 == ui->checkBox_eng->checkState() && arg1 == ui->checkBox_jp->checkState()){
        state = (Qt::CheckState)arg1;
    } else {
        state = Qt::PartiallyChecked;
    }

    ui->checkBox_co->blockSignals(true);
    ui->checkBox_co->setCheckState( state);
    ui->checkBox_co->blockSignals(false);
}

void MainWindow::on_checkBox_eng_stateChanged(int arg1)
{
    Qt::CheckState state;

    if (arg1 == ui->checkBox_chi->checkState() && arg1 == ui->checkBox_jp->checkState()){
        state = (Qt::CheckState)arg1;
    } else {
        state = Qt::PartiallyChecked;
    }
    ui->checkBox_co->blockSignals(true);
    ui->checkBox_co->setCheckState( state);
    ui->checkBox_co->blockSignals(false);
}

void MainWindow::on_checkBox_jp_stateChanged(int arg1)
{
    Qt::CheckState state;

    if (arg1 == ui->checkBox_chi->checkState() && arg1 == ui->checkBox_eng->checkState()){
        state = (Qt::CheckState)arg1;
    } else {
        state = Qt::PartiallyChecked;
    }

    ui->checkBox_co->blockSignals(true);
    ui->checkBox_co->setCheckState( state);
    ui->checkBox_co->blockSignals(false);
}
