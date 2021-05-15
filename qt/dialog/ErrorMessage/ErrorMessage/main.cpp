#include "ErrorMessage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ErrorMessage w;
    w.show();
    return a.exec();
}
