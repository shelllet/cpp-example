#pragma once
#include "framework.h"
#include <qabstractsocket.h>
#include "network_module.h"
#include "qabstractsocket_p.h"
#include "qabstractsocket_wrapper.h"

namespace shelllet {
	namespace network {
		class AbstractSocket : public QAbstractSocketWrapper<QAbstractSocket, AbstractSocket, true>
		{
		public:
				AbstractSocket(const v8::FunctionCallbackInfo<v8::Value>& args);
			AbstractSocket(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
