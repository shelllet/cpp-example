#pragma once
#include "items_callback.h"
#include "pugixml.hpp"

namespace shelllet {
	namespace creator {
		class New : public CallbackMessage
		{
		public:
			virtual void messageCallback(Callback* call);
		};
	}
}
