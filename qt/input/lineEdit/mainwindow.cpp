#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QIcon>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto* validator = new QRegularExpressionValidator(QRegularExpression(R"(\w+@\w+\.\w+)"));

    ui->lineEdit->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setCursorPosition(ui->lineEdit_2->text().toInt());
    ui->lineEdit->setFocus();
    qDebug() << "called " << ui->lineEdit->cursorPosition();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setDragEnabled(!ui->lineEdit->dragEnabled());
}

void MainWindow::on_pushButton_3_clicked()
{
    QIcon icon = QIcon("D:\\qt\\A\\input\\lineEdit\\gamer-Sticker-by-Adimanav.jpg");

    if (icon.isNull()) {
        qDebug() << "null icon";
    }
    QAction* action = new QAction(icon, "icon");

      ui->lineEdit->addAction(action, QLineEdit::LeadingPosition);
      qDebug() << "action called ";
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug()<< ui->lineEdit->hasAcceptableInput();
}
