#include "DateTime.h"
#include <QDebug>

//https://bugreports.qt.io/browse/QTBUG-34759
DateTime::DateTime(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
