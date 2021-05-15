#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QDebug>
#define MAX_PAGE_COUNT 3

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(new QCheckBox(this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
   static int i = 0;

   if (++i >=MAX_PAGE_COUNT){ i = 0;}
    ui->stackedWidget->setCurrentIndex(i %MAX_PAGE_COUNT );

}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    qDebug() << "current changed...";
}
