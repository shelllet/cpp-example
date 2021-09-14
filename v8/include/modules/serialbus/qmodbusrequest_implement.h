#pragma once
#include "framework.h"
#include <qmodbuspdu.h>
#include "qmodbusrequest_p.h"
#include "qmodbusrequest_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusRequest : public QModbusRequestWrapper<QModbusRequest, ModbusRequest, true>
		{
		public:
			using ReturnType = QModbusRequestPrivate<QModbusRequest, true>;
			using ReturnType2 = QModbusRequestPrivate<QModbusRequest, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusRequest(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusRequestWrapper(*Private(args), args)
			{
			}
			ModbusRequest(QModbusRequest* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusRequestWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusRequest(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusRequestWrapper(isolate, tpl) {}
			ModbusRequest(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusRequestWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusRequest"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
