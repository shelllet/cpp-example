#include "MessageBox.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MessageBox w;
    w.show();
    return a.exec();
}
