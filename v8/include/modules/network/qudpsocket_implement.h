#pragma once
#include "framework.h"
#include "network_module.h"
#include "qudpsocket_p.h"
#include "qudpsocket_wrapper.h"

namespace shelllet {
	namespace network {
		class UdpSocket : public QUdpSocketWrapper<QUdpSocket, UdpSocket, true>
		{
		public:
			UdpSocket(const v8::FunctionCallbackInfo<v8::Value>& args);
			UdpSocket(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
