#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#include <QMovie>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QMovie* movie = new QMovie(QString::fromStdWString(L"./Screen.mp4"));
    QMovie* movie = new QMovie(QString::fromStdWString(L"./timg.gif"));
    ui->label_5->setMovie(movie);
    movie->start();

   /// ui->label->setPixmap(QPixmap("./231102-151931226201f1.jpg"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

