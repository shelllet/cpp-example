#include "Spinbox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Spinbox w;
    w.show();
    return a.exec();
}
