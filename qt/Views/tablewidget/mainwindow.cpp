#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tableWidget->item(0, 0)->setText("a");


    ui->tableWidget->setCellWidget(0, 1, new QPushButton("button"));
    assert(ui->tableWidget->cellWidget(0,1));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    qDebug() << "#" << "this is double clicked";
}
