#include <qboxlayout.h>
#include "creator_panel.h"
#include "main_window.h"
#include "wizard/splash_guide.h"
#include "private/qobject_p.h"
#include "events.hpp"
#include "frameless.hpp"
#include "qdesktopwidget.h"
#include "qapplication.h"
#include "qstyle.h"
#include "qsize.h"
#include "qscreen.h"
#include "creator/component.h"
#include "frameless/private/mainwindow_p.h"

namespace shelllet {
	namespace creator {
		class AppWindowPrivate : public MainWindowPrivate {
		public:
			std::map<ResponseHandler::Exit, std::function<void()>> funcs;
			WizardWidget* wizardWidget = nullptr;
	
		};
	}
}

shelllet::creator::AppWindow::AppWindow(QWidget* parent)
	: MainWindow(*new AppWindowPrivate, parent, WindowType::AllButton)
{
	Q_D(AppWindow);

	d->wizardWidget = new WizardWidget(this);
	setWindowTitle(Environment::getInstance()->getOptions()->applicationName);
	setCentralWidget(new CreatorPanel);

	//properties_component::registerAllProperties();
	d->funcs[ResponseHandler::Exit::Create] = std::bind(&AppWindow::create, this);
	d->funcs[ResponseHandler::Exit::Open] = std::bind(&AppWindow::open, this);
	d->funcs[ResponseHandler::Exit::FromGit] = std::bind(&AppWindow::fromGit, this);

	//d->wizardWidget->setWindowModality(Qt::WindowModality::ApplicationModal);
}

shelllet::creator::AppWindow::~AppWindow()
{
}

void shelllet::creator::AppWindow::finshed(Exit exit)
{
	Q_D(AppWindow);
	if (d->funcs.contains(exit)) {
		d->funcs[exit]();
		d->wizardWidget->close();
	}
}

void shelllet::creator::AppWindow::show()
{
	Q_D(AppWindow);
	QSize size = QApplication::primaryScreen()->availableSize() * 0.8;

	setWindowIcon(qApp->windowIcon());
	resize(size);
	moveToCentral();
	showNormal();
	d->wizardWidget->show();
}

void shelllet::creator::AppWindow::create()
{
	Q_D(AppWindow);
	dynamic_cast<CreatorPanel*>(centralWidget())->create();
}

void shelllet::creator::AppWindow::fromGit()
{
	Q_D(AppWindow);
	dynamic_cast<CreatorPanel*>(centralWidget())->git();
}

void shelllet::creator::AppWindow::open()
{
	Q_D(AppWindow);
	dynamic_cast<CreatorPanel*>(centralWidget())->open();
}
