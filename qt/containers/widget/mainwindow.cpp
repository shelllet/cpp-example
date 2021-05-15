#include "mainwindow.h"
#include <QPushButton>
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>
#include<QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QWhatsThis>
#include <QPalette>


class PushButton : public QPushButton{
public:
    PushButton(QString text): QPushButton(text){
        setMouseTracking(true);
        setAcceptDrops(true);
        this->setWindowTitle("widget");
    }
    void mouseMoveEvent(QMouseEvent*){

         //qDebug() << "mouse event";
    }



};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->lineEdit->addAction(new QAction("menu"));


    ui->centralWidget->layout()->addWidget(new PushButton("Text"));

    connect(ui->lineEdit, &QLineEdit::customContextMenuRequested, [](){

        qDebug() << "customContextMenuRequested";

    });


    QPalette pal;


    pal.setColor(QPalette::Window, Qt::red);

    ui->label->setPalette(pal);


   // qDebug() << ui->pushButton->geometry();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (QWhatsThis::inWhatsThisMode()) {
        qDebug() << "in";
        QWhatsThis::leaveWhatsThisMode();
    } else{
    qDebug() << "out";
        QWhatsThis::enterWhatsThisMode();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *)
{

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << __FUNCTION__;
    event->accept();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
 qDebug() << __FUNCTION__;
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
 qDebug() << __FUNCTION__;
}

void MainWindow::dropEvent(QDropEvent *event)
{
 qDebug() << __FUNCTION__;
}
