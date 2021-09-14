#include "common.hpp"
#include "events/activity_create_event.h"

using namespace shelllet::events;
ActivityCreateEvent::ActivityCreateEvent(const String& meta)
	: QEvent(ActivityCreateEvent::Type)
	, meta_(meta)
{
}

String shelllet::events::ActivityCreateEvent::meta() const
{
	return meta_;
}