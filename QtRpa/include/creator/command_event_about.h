#pragma once
#include "items_callback.h"
namespace shelllet {
	namespace creator {
		class About : public CallbackMessage
		{
		protected:
			virtual void messageCallback(Callback* call);
		private:
		};
	}
}
