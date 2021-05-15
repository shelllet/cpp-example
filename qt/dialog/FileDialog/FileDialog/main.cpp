#include "FileDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileDialog w;
    w.show();
    return a.exec();
}
