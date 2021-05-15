#include "ErrorMessage.h"
#include "qerrormessage.h"
#include "qdebug.h"
ErrorMessage::ErrorMessage(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    auto* dialog = QErrorMessage::qtHandler();


    connect(ui.pushButton, &QPushButton::clicked, [this]() {
        
        QErrorMessage dialog;
        dialog.showMessage("This is test message.");
        dialog.exec();
        });


	connect(ui.pushButton_2, &QPushButton::clicked, [this]() {

        qDebug() << "# error message test.";
	
		});
}
