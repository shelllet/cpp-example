#include "common.hpp"
#include <filesystem>
#include <QCoreApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QTextEdit>
#include "creator/about_window.h"
#include "common/path.h"

shelllet::creator::AboutWindow::AboutWindow(QWidget* parent /*= nullptr*/)
	: MainWindow(parent, WindowType::CloseButtonHint)
{
	auto* centralWidget = new QWidget;

	auto* layout = new QHBoxLayout(centralWidget);
	auto* background = new QLabel;
	background->setPixmap(Environment::getInstance()->pixmap("/photo.jpg"));
	background->setScaledContents(true);
	layout->addWidget(background);

	auto* vlay = new QVBoxLayout;
	auto* textEdit = new QTextEdit(centralWidget);

	textEdit->setEnabled(false);

	textEdit->setHtml(tr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
		"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
		"p, li { white-space: pre-wrap; }\n"
		"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
		"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:600;\">Studio - Robot</span></p>\n"
		"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
		"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:11pt;\">Version: 0.5.0</span></p>\n"
		"<p style=\" margin-top:0px; margin-bottom:0px;"
		" margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:11pt;\">Url: http://shelllet.com</span></p></body></html>"));
	textEdit->setFixedWidth(240);
	vlay->addWidget(textEdit);
	layout->addLayout(vlay);

	setFixedSize(600, 420);

	setCentralWidget(centralWidget);
}

shelllet::creator::AboutWindow::~AboutWindow()
{
}