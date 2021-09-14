#include "events/closeevent.h"


shelllet::events::CloseEvent::CloseEvent(int result)
	:QEvent(CloseEvent::Type)
	, result(result)
{

}
