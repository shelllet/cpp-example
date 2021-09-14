#pragma once
#include "framework.h"
#include <qmodbustcpclient.h>
#include "qmodbustcpclient_p.h"
#include "qmodbustcpclient_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusTcpClient : public QModbusTcpClientWrapper<QModbusTcpClient, ModbusTcpClient, true>
		{
		public:
			using ReturnType = QModbusTcpClientPrivate<QModbusTcpClient, true>;
			using ReturnType2 = QModbusTcpClientPrivate<QModbusTcpClient, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusTcpClient(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusTcpClientWrapper(*Private(args), args)
			{
			}
			ModbusTcpClient(QModbusTcpClient* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusTcpClientWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusTcpClient(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusTcpClientWrapper(isolate, tpl) {}
			ModbusTcpClient(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusTcpClientWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusTcpClient"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
