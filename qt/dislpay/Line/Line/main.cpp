#include "Line.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Line w;
    w.show();
    return a.exec();
}
