#pragma once
#include "framework.h"
#include <qmodbuspdu.h>
#include "qmodbusresponse_p.h"
#include "qmodbusresponse_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusResponse : public QModbusResponseWrapper<QModbusResponse, ModbusResponse, true>
		{
		public:
			using ReturnType = QModbusResponsePrivate<QModbusResponse, true>;
			using ReturnType2 = QModbusResponsePrivate<QModbusResponse, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusResponse(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusResponseWrapper(*Private(args), args)
			{
			}
			ModbusResponse(QModbusResponse* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusResponseWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusResponse(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusResponseWrapper(isolate, tpl) {}
			ModbusResponse(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusResponseWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusResponse"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
