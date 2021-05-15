#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_groupBox_toggled(bool arg1)
{
    qDebug() << "toggle" << arg1;
}

void MainWindow::on_groupBox_clicked(bool checked)
{
    qDebug() << "clicked:" << checked;
}
