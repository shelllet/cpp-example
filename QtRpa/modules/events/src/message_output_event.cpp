#include "events/message_output_event.h"

shelllet::events::MessageOutputEvent::MessageOutputEvent(const std::string& msg)
	: QEvent(MessageOutputEvent::Type)
	, message_(msg)
{
}

std::string shelllet::events::MessageOutputEvent::message() const
{
	return message_;
}