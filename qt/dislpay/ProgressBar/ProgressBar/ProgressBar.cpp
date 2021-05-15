#include "ProgressBar.h"

ProgressBar::ProgressBar(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, [this]() {

		ui.progressBar->setMaximum(100);
		ui.progressBar->setValue(0);

		/// <summary>
		///  long work.
		/// </summary>
		/// <param name="parent"></param>
		for (int i = 0; i < 100; i++) {
			ui.progressBar->setValue(i);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			QApplication::processEvents();
		}

		});
}