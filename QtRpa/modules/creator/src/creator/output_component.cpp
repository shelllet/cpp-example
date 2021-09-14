#include "common.hpp"
#include "output_component.h"
#include "events/message_output_event.h"
#include "events/common_event.h"
using namespace shelllet::creator;
OutputComponent::OutputComponent(QWidget* parent)
{
	events::EventDispatcher::Dispatcher()->push(this);
}

OutputComponent::~OutputComponent()
{
}

void shelllet::creator::OutputComponent::customEvent(QEvent* event)
{
	auto* e = dynamic_cast<events::MessageOutputEvent*>(event);
	if (e) {
		addItem(new QListWidgetItem(QString::fromStdString(e->message())));
	}
}