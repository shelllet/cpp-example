#include "LCDNumber.h"
#include <QDebug>
LCDNumber::LCDNumber(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.lcdNumber, &QLCDNumber::overflow, []() {
        
        qDebug() << "# overflow.";
        });

    connect(ui.pushButton, &QPushButton::clicked, [this]() {
        
        auto text = ui.lineEdit->text();

        ui.lcdNumber->display(text.toInt());

        
        });
}
