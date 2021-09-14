#pragma once
#include "framework.h"
#include "network_module.h"
#include "qwebsocketserver_p.h"
#include "qwebsocketserver_wrapper.h"

namespace shelllet {
	namespace network {
		class WebSocketServer : public QWebSocketServerWrapper<QWebSocketServer, WebSocketServer, true>
		{
		public:
			WebSocketServer(const v8::FunctionCallbackInfo<v8::Value>& args);
			WebSocketServer(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);
		public:
			static const char* Name();
		};
	}
}
