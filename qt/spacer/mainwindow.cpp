#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->layoutCenter_ = new QHBoxLayout(ui->centralWidget);

    this->frame_ = new QFrame(ui->centralWidget);

    layoutCenter_->addWidget(this->frame_);
    layout_ = new QHBoxLayout(this->frame_);

    button1_ = new QPushButton(this->frame_);
    button1_->setMinimumWidth(175);
    button1_->setFixedHeight(36);
    button1_->setText("button1");


    layout_->addWidget(button1_);

    button2_ = new QPushButton(this->frame_);

    button2_->setMinimumWidth(175);
    button2_->setFixedHeight(36);
    button2_->setText("button2");

    layout_->addWidget(button2_);

    spacerItem_ = new QSpacerItem(20, 20, QSizePolicy::Expanding);

    layout_->addItem(spacerItem_);


    button3_ = new QPushButton(this->frame_);

    button3_->setMinimumWidth(175);
    button3_->setFixedHeight(36);
    button3_->setText("button3");

    layout_->addWidget(button3_);

}

MainWindow::~MainWindow()
{
    delete ui;
}
