#include "events/gitcloneevent.h"

shelllet::events::GitCloneEvent::GitCloneEvent()
	: QEvent(GitCloneEvent::Type)
{

}
