#include "FileDialog.h"
#include "qfiledialog.h"
#include <qstandardpaths.h>

FileDialog::FileDialog(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, [this]() {
        auto picture = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

      auto file =  QFileDialog::getOpenFileName(this, "Open filename", picture, "Png(*.png *.jpg);;All files(*)");


      ui.lineEdit->setText(file);


        });

	connect(ui.pushButton_2, &QPushButton::clicked, [this]() {
		auto picture = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

		auto file = QFileDialog::getOpenFileUrl(this, "Open filename", QUrl(picture), "Png(*.png *.jpg);;All files(*)");


		ui.lineEdit->setText(file.toString());


		});


	connect(ui.pushButton_3, &QPushButton::clicked, [this]() {
		auto picture = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);

		auto file = QFileDialog::getOpenFileUrl(this, "Open filename", QUrl(picture), "Png(*.png *.jpg);;All files(*)", nullptr,
			QFileDialog::Option::DontUseNativeDialog);


		ui.lineEdit->setText(file.toString());


		});
}
