#include "MessageBox.h"
#include "qmessagebox.h"
#include "qdebug.h"
MessageBox::MessageBox(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_about, &QPushButton::clicked, [this]() {
        QMessageBox::about(this, "about", "this is a about dialog.");
        });

	connect(ui.pushButton_aboutqt, &QPushButton::clicked, [this]() {
		QMessageBox::aboutQt(this, "aboutqt");
		});


	connect(ui.pushButton_critical, &QPushButton::clicked, [this]() {
		qDebug() <<  QMessageBox::critical(this, "critical", "this is a critical dialog.");
		});

	connect(ui.pushButton_info, &QPushButton::clicked, [this]() {
		qDebug() << QMessageBox::information(this, "information", "this is a information dialog.");
		});
	connect(ui.pushButton_quest, &QPushButton::clicked, [this]() {
		qDebug() <<QMessageBox::question(this, "question", "this is a question dialog.");
		});


	connect(ui.pushButton_warning, &QPushButton::clicked, [this]() {
		qDebug() << QMessageBox::warning(this, "warning", "this is a warning dialog.");
		});
}
