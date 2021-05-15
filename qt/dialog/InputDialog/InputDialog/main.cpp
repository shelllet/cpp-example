#include "InputDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InputDialog w;
    w.show();
    return a.exec();
}
