#include "creator.hpp"
#include "creator/command_event_about.h"
#include "creator/about_window.h"
void shelllet::creator::About::messageCallback(Callback* call)
{
	auto* parent = dynamic_cast<QWidget*>(call);

	auto * about = new AboutWindow(parent);
	about->setAttribute(Qt::WA_DeleteOnClose);
	about->show();
}