#include "FontDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FontDialog w;
    w.show();
    return a.exec();
}
