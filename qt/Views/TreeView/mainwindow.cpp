#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QList<QStandardItem*> list;

    auto item = new QStandardItem("浙江省");


    auto hz = new QStandardItem("杭州");

    hz->appendRow(new QStandardItem("西湖区"));
    hz->appendRow(new QStandardItem("上城区"));
    item->appendRow(hz);




    item->appendRow(new QStandardItem("金华"));
    item->appendRow(new QStandardItem("衢州"));


    list.push_back(item);

    model.appendRow(list);


    ui->treeView->setModel(&model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

