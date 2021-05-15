#include "Dialog.h"
#include "qcolordialog.h"
#include "qdebug.h"
Dialog::Dialog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [this]() {
        QColorDialog dialog;

        connect(&dialog, &QColorDialog::colorSelected, [](auto& color) {
            qDebug() << "# select color: " << color;
            });
        dialog.exec();

        });
}
