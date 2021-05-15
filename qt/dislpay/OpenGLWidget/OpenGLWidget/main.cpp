#include "OpenGLWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGLWidget w;
    w.show();
    return a.exec();
}
