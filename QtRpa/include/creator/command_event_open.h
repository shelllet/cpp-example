#pragma once
#include "items_callback.h"

namespace shelllet {
	namespace creator {
		class Open : public CallbackMessage
		{
		protected:
			virtual void messageCallback(Callback* call);
		};
	}
}
