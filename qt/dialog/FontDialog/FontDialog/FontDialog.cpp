#include "FontDialog.h"
#include "qfontdialog.h"
#include "qdebug.h"
FontDialog::FontDialog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [this]() {

        bool ok = false;
     auto font=    QFontDialog::getFont(&ok, this);
     if (ok)
        ui.plainTextEdit->setFont(font);
     else {
         
     }
     qDebug() << font.family();
        
        });
}
