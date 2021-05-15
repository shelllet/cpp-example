#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // {
        QTranslator trans;

        if(    trans.load("qtbase_zh_Cn.qm")){
            a.installTranslator(&trans);
        }
   // }

        QTranslator trans2;

        if(    trans2.load("test.qm")){
            a.installTranslator(&trans2);
        }

    MainWindow w;
    w.show();
    return a.exec();
}
