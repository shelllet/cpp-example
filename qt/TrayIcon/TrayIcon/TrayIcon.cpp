#include "TrayIcon.h"
#include "QApplication"
TrayIcon::TrayIcon(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	trayIcon.setToolTip("this is tray icon demo");

	trayIcon.setIcon(QIcon(":/TrayIcon/icon"));


	// trayIcon.setVisible(true);

	menu.addAction("Exit", [](...) {
		QApplication::quit();
		});

	//trayIcon.setContextMenu(&menu);

	connect(&trayIcon, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {

		if (reason == QSystemTrayIcon::DoubleClick)
			this->showNormal();
		else if (reason == QSystemTrayIcon::Context) {
			// TODO:

			menu.popup(QCursor::pos());
		}
		});

	trayIcon.show();
}
