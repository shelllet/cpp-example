#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    labelUser_ = new QLabel(ui->centralWidget);
    labelPassword_ = new QLabel(ui->centralWidget);

    labelUser_->setText("userName");
    labelPassword_->setText("password");


    fieldUser_ = new QLineEdit(ui->centralWidget);
    fieldPassword_ = new QLineEdit(ui->centralWidget);


    layout_ =  new QFormLayout(ui->frame);


    layout_->addRow(labelUser_, fieldUser_);

    layout_->addRow(labelPassword_, fieldPassword_);


}

MainWindow::~MainWindow()
{
    delete ui;
}
