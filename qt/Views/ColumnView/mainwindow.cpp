#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->columnView->setColumnWidths({80, 120, -1});
    for(auto i = 0; i < 5; i++){
        auto group = new QStandardItem(QString("%1").arg(i));

        for( auto ii = 0; ii < 10; ii++){

            group->appendRow(new QStandardItem(QString("%1").arg(ii)));

        }

        model_.appendRow(group);
    }


   ui->columnView->setModel(&model_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

