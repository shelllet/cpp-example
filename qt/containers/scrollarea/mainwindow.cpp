#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget(ui->label);
   // ui->scrollArea->setWidget(ui->pushButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->scrollArea->ensureWidgetVisible(ui->label);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->scrollArea->ensureVisible(arg1, 100);
}
