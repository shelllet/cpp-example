#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dialog1_ = std::make_unique<Dialog1>();
    dialog2_ = std::make_unique<Dialog2>();



    layout_ = new QStackedLayout(ui->frame);

    layout_->addWidget(dialog1_.get());
    layout_->addWidget(dialog2_.get());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    layout_->setCurrentWidget(dialog1_.get());
}

void MainWindow::on_pushButton_2_clicked()
{
    layout_->setCurrentWidget(dialog2_.get());
}
