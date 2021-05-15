#include "Menu.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu w;
    w.show();
    return a.exec();
}
