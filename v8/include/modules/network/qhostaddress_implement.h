#pragma once
#include "framework.h"
#include <qhostaddress.h>
#include "network_module.h"
#include "qhostaddress_p.h"
#include "qhostaddress_wrapper.h"

namespace shelllet {
	namespace network {
		class HostAddress : public QHostAddressWrapper<QHostAddress, HostAddress, true>
		{
		public:
				HostAddress(const v8::FunctionCallbackInfo<v8::Value>& args);
			HostAddress(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

			static const char* Name();
		};
	}
}
