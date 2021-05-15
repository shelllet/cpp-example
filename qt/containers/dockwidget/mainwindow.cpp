#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLineEdit>
#include <form.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


        qDebug() <<"text:" << ui->dockWidget->toggleViewAction()->text();

        auto * form = new Form;
        connect(form, &Form::closeClicked, [this](){
            ui->dockWidget->hide();
        });
        ui->dockWidget->setTitleBarWidget(form);
        ui->dockWidget_2->toggleViewAction()->setToolTip("tip");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
   {
    ui->dockWidget->toggleViewAction()->setText("abc");
    qDebug() <<"text:" << ui->dockWidget->toggleViewAction()->text();



    ui->dockWidget->setWindowTitle("abc");

    ui->dockWidget->show();

    ui->dockWidget_2->toggleViewAction()->trigger();


}
