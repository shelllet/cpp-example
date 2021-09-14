#pragma once
#include "framework.h"
#include "network_module.h"
#include "qtcpserver_p.h"
#include "qtcpserver_wrapper.h"

namespace shelllet {
	namespace network {
		class TcpServer : public QTcpServerWrapper<QTcpServer, TcpServer, true>
		{
		public:
			TcpServer(const v8::FunctionCallbackInfo<v8::Value>& args);
			TcpServer(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
