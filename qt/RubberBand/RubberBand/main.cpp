#include "RubberBand.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RubberBand w;
    w.show();
    return a.exec();
}
