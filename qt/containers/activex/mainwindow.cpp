#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_pushButton_clicked()
{
    ui->axWidget->dynamicCall(qPrintable( QString("Navigate(\"%1\")").arg(ui->lineEdit->text())));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->axWidget->dynamicCall("GoBack()");
}
