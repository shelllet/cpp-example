#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
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


void MainWindow::on_actionoptional_triggered()
{
    Dialog dlg;
   auto result = dlg.exec();

   if (result == QDialog::Accepted){

    auto option = dlg.getOption();


    qDebug() <<"math: " << option.math << "\n"
            << "chinese: " << option.chinese << "\n"
            << "english: " << option.english;
   }
    else{
       qDebug() << "reject.";
   }

}
