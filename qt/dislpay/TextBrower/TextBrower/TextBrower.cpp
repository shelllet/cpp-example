#include "TextBrower.h"
#include <QDesktopServices>
#include <QDebug>
TextBrower::TextBrower(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textBrowser->setSearchPaths({"./img"});
	ui.textBrowser->setSource(QUrl::fromLocalFile("./hello.html"), QTextDocument::ResourceType::HtmlResource);


	qDebug() << "html:" << ui.textBrowser->toHtml();

	connect(ui.textBrowser, &QTextBrowser::anchorClicked, [](const QUrl& link) {
		qDebug() << link;
		//QDesktopServices::openUrl(link);
		});

	connect(ui.pushButton, &QPushButton::clicked, [this]() {

		ui.textBrowser->backward();
		});
	connect(ui.pushButton_2, &QPushButton::clicked, [this]() {
		ui.textBrowser->forward();
		});
	connect(ui.pushButton_3, &QPushButton::clicked, [this]() {
		qDebug() << "html:" << ui.textBrowser->toHtml();
		});
}
