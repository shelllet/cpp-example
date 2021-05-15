#include "ProgressDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgressDialog w;
    w.show();
    return a.exec();
}
