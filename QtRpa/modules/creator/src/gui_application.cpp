#include "creator.hpp"
#include "creator/gui_application.h"
#include "common/kernel.h"
#include "common/common_widget.h"
#include "events/common_event.h"
#include "creator/main_window.h"
#include "common/format.h"
#include <qmenu.h>
//#include "properties/helper.h"
#include <qsystemtrayicon.h>
#include <qmenu.h>
#include <qsqldatabase.h>
#include <boost/thread/thread_guard.hpp>
#include <boost/thread.hpp>
#include "creator/main_window.h"
#include "frameless.hpp"
#include "common.hpp"
#include "wizard.hpp"
#include "common/private/object_p.h"
#include "qapplication.h"
#include "interpreter.hpp"
namespace shelllet {
	namespace creator {
		class GuiApplicationPrivate : public ObjectPrivate {
		public:
			QMenu menu;
			QSystemTrayIcon tray;
			AppWindow mainWindow;
		};

		Q_GLOBAL_STATIC(GuiApplication, __GuiApplication__)
	}
}
shelllet::creator::GuiApplication::GuiApplication()
	: Object(*new GuiApplicationPrivate, nullptr)
{
	common::glFormat->initialize(__argc, __argv);

	//ConsoleApplication::getInstance()->initialize();
	//	Helper::register_meta_type();
}


void shelllet::creator::GuiApplication::run(QEvent*)
{
	Q_D(GuiApplication);
	BOOST_ASSERT(QSqlDatabase::isDriverAvailable("QSQLITE"));

	QSqlDatabase::addDatabase("QSQLITE");

	d->menu.addAction(QObject::tr("Show"), [&]() { d->mainWindow.show(); });
	d->menu.addAction(QObject::tr("Exit"), [&]() {
		QApplication::quit();
	});
	d->tray.setIcon(qApp->windowIcon());
	d->tray.setContextMenu(&d->menu);
	QObject::connect(&d->tray, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason) {
		if (QSystemTrayIcon::DoubleClick == reason) {
			d->mainWindow.show();
		}});

	d->tray.show();
	d->mainWindow.show();
}

shelllet::creator::GuiApplication* shelllet::creator::GuiApplication::getInstance()
{
	return __GuiApplication__;
}
