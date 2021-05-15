#include "SpliterRubberBand.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpliterRubberBand w;
    w.show();
    return a.exec();
}
