#include "TextBrower.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextBrower w;
    w.show();
    return a.exec();
}
