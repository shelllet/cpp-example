#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

         list << "a" << "b" << "c";
         model.setStringList(list);

         ui->listView->setModel(&model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

