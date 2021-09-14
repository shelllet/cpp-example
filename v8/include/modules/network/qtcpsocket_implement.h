#pragma once
#include "framework.h"
#include "network_module.h"
#include "qtcpsocket_p.h"
#include "qtcpsocket_wrapper.h"

namespace shelllet {
	namespace network {
		class TcpSocket : public QTcpSocketWrapper<QTcpSocket, TcpSocket, true>
		{
		public:
			TcpSocket(const v8::FunctionCallbackInfo<v8::Value>& args);
			TcpSocket(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
