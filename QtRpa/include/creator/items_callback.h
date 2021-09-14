#pragma once
namespace shelllet {
	namespace creator {
		class Callback;

		class CallbackMessage {
		public:
			virtual ~CallbackMessage() {}
		};

		class Callback {
		public:
			virtual void callbk(CallbackMessage*, int num, ...) = 0;
		};
	}
}
