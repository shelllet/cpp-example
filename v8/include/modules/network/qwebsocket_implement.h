#pragma once
#include "framework.h"
#include "network_module.h"
#include "qwebsocket_p.h"
#include "qwebsocket_wrapper.h"

namespace shelllet {
	namespace network {
		class WebSocket : public QWebSocketWrapper<QWebSocket, WebSocket, true>
		{
		public:
			WebSocket(const v8::FunctionCallbackInfo<v8::Value>& args);
			WebSocket(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
