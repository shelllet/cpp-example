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

void MainWindow::on_radioButton_2_clicked()
{
    static int index = 0;
    qDebug() << "clicked: "<< index++ ;
}


void MainWindow::on_radioButton_clicked()
{

       ui->radioButton_2->setChecked(!ui->radioButton_2->isChecked());

}
