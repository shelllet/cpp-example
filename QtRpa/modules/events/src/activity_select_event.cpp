#include "common.hpp"
#include "interpreter/composite_property.h"
#include "events/activity_select_event.h"

using namespace shelllet::events;
ActivitySelectEvent::ActivitySelectEvent(shelllet::interpreter::CompositeProperty* prop)
	: QEvent(ActivitySelectEvent::Type)
	, prop_(prop)
{
}

shelllet::interpreter::CompositeProperty* ActivitySelectEvent::getProp() const
{
	return prop_;
}