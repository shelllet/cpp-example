#include "Thread.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Thread w;
    w.show();
    return a.exec();
}
