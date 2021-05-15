#include "mainwindow.h"
#include <QApplication>
#include <QPalette>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    QPalette pal;


    pal.setColor(QPalette::Window, Qt::red);

    w.setPalette(pal);
            w.show();

    return a.exec();
}
