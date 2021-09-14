#pragma once
#include "framework.h"
#include "network_module.h"
#include "qnetworkdatagram_p.h"
#include "qnetworkdatagram_wrapper.h"

namespace shelllet {
	namespace network {
		class NetworkDatagram : public QNetworkDatagramWrapper<QNetworkDatagram, NetworkDatagram, true>
		{
		public:
			NetworkDatagram(const v8::FunctionCallbackInfo<v8::Value>& args);
			NetworkDatagram(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

		public:
			static const char* Name();
		};
	}
}
