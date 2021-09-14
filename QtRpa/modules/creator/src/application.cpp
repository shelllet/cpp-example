#include <QApplication>
#include "creator/application.h"
#include "creator/private/application_p.h"
#include "events.hpp"
#include "interpreter.hpp"
#include "creator/gui_application.h"
#include "interpreter/consoleapplication.h"
namespace shelllet {
	namespace creator {

	}
}
shelllet::creator::ApplicationPrivate::__Application::__Application(shelllet::creator::Application* self, int& argc, char** argv)
	: QApplication(argc, argv)
	, self(self)
{

}

void shelllet::creator::ApplicationPrivate::__Application::customEvent(QEvent* event)
{
	self->customEvent(event);
}

shelllet::creator::Application::Application(ApplicationPrivate& d, int& argc, char** argv, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

	d.app = std::make_unique<ApplicationPrivate::__Application>(this, argc, argv);
}

void shelllet::creator::Application::customEvent(QEvent* event)
{

	if (auto* e = dynamic_cast<ConsoleEvent*>(event)) {
		ConsoleApplication::getInstance()->initialize();
		ConsoleApplication::getInstance()->run(e);
	}
	else if (dynamic_cast<GuiEvent*>(event)) {
		ConsoleApplication::getInstance()->initialize();
		GuiApplication::getInstance()->run(e);
	}
}

void shelllet::creator::Application::setWindowIcon(const QIcon& icon)
{
	Q_D(Application);
	d->app->setWindowIcon(icon);
}

void shelllet::creator::Application::setQuitOnLastWindowClosed(bool quit)
{
	Q_D(Application);
	d->app->setQuitOnLastWindowClosed(quit);
}

QApplication* shelllet::creator::Application::toQApplication() const
{
	Q_D(const Application);
	return d->app.operator ->();
}

shelllet::creator::Application::Application(int& argc, char** argv, Object* parent /*= nullptr*/)
	:Application(*new ApplicationPrivate, argc, argv, parent)
{
}
