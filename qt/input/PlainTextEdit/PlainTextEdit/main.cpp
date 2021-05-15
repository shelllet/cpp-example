#include "PlainTextEdit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlainTextEdit w;
    w.show();
    return a.exec();
}
