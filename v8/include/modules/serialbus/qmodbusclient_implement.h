#pragma once
#include "framework.h"
#include <qmodbusclient.h>
#include "qmodbusclient_p.h"
#include "qmodbusclient_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusClient : public QModbusClientWrapper<QModbusClient, ModbusClient, true>
		{
		public:
			using ReturnType = QModbusClientPrivate<QModbusClient, true>;
			using ReturnType2 = QModbusClientPrivate<QModbusClient, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusClient(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusClientWrapper(*Private(args), args)
			{
			}
			ModbusClient(QModbusClient* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusClientWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusClient(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusClientWrapper(isolate, tpl) {}
			ModbusClient(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusClientWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusClient"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
