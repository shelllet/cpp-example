#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layout_ = new QGridLayout(ui->centralWidget);

    size_t index = 0;
    for (int i = 0; i < 3; ++i) {

        for (int j = 0; j< 3; ++j) {
            buttons_[index] = new QPushButton(QString("%1*%2=%3").arg(i).arg(j).arg(i*j), ui->centralWidget);
            layout_->addWidget(buttons_[index], i, j);
            index++;
        }

    }

    layout_->setSpacing(9);
}

MainWindow::~MainWindow()
{
    delete ui;
}
