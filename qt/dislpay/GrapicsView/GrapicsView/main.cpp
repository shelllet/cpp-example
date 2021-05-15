#include "GrapicsView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GrapicsView w;
    w.show();
    return a.exec();
}
