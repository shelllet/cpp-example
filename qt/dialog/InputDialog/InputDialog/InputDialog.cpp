#include "InputDialog.h"
#include "qinputdialog.h"
#include "qdebug.h"
InputDialog::InputDialog(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, [this]() {
		auto text = QInputDialog::getMultiLineText(this, "test", "description:");
		qDebug() << text;
		});
}
