#include "creator.hpp"
void shelllet::creator::Exec::messageCallback(Callback* call)
{
	call->callbk(this, 0);
}