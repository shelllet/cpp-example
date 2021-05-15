#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QPushButton>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(new Dialog, "dialog" );

    auto * btn = new QPushButton("corner");
    connect(btn, &QPushButton::clicked, [](){

        qDebug() << "clicked";
    });
    ui->tabWidget->setCornerWidget(btn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    auto *w = dynamic_cast<AbstractEdit*>(ui->tabWidget->widget(index));

    if (w){
        w->setText(QString::fromStdString(std::to_string(index)));
    }

}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
