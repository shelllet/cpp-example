
#include "creator.hpp"

void shelllet::creator::Save::messageCallback(Callback* call)
{
	call->callbk(this, 0);
	//ActionProjectSaveBroadcaster::getInstance()->emit();
}