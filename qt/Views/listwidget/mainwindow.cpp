#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem(new QListWidgetItem("广东省"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    Dialog dlg;
    dlg.setWindowTitle(item->text());
    dlg.exec();
}

void MainWindow::on_pushButton_clicked()
{

    auto*  item = ui->listWidget->currentItem();

    ui->listWidget->removeItemWidget(item);
    delete item;
   // delete item;
  // auto * item = ui->listWidget->takeItem(ui->listWidget->currentRow());

  // delete item;
}
