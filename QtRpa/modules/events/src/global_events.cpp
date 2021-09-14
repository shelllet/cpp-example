#include <qcoreapplication.h>
#include "events/common_event.h"

using namespace shelllet::events;
ActivitiesShowEvent::ActivitiesShowEvent(/*QTreeWidgetItem* item*/)
	: QEvent(ActivitiesShowEvent::eType)
	//, item(item)
{
}
//
//QTreeWidgetItem* shelllet::events::ActivitiesShowEvent::getItem() const
//{
//	return item;
//}

void shelllet::events::EventDispatcher::push(QObject* receiver)
{
	concerns.push_back(receiver);
}

void shelllet::events::EventDispatcher::customEvent(QEvent* event)
{
	for (int i = 0; i < concerns.size(); ++i) {
		QCoreApplication::sendEvent(concerns.at(i), event);
	}
}

shelllet::events::EventDispatcher::EventDispatcher() {
}