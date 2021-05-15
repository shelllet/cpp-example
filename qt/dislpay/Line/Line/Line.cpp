#include "Line.h"
#include <qpalette.h>
Line::Line(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.line->setStyleSheet("");


    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);

    ui.line->setPalette(palette);
}
