#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appendtext.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->undoView->setStack(&stack);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    stack.push(new AppendText(ui->label, ui->lineEdit->text()));
}

void MainWindow::on_pushButton_2_clicked()
{
    stack.redo();
}

void MainWindow::on_pushButton_3_clicked()
{
    stack.undo();
}
