#pragma once
#include "framework.h"
#include <qmodbusdevice.h>
#include "qmodbusdevice_p.h"
#include "qmodbusdevice_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusDevice : public QModbusDeviceWrapper<QModbusDevice, ModbusDevice, true>
		{
		public:
			using ReturnType = QModbusDevicePrivate<QModbusDevice, true>;
			using ReturnType2 = QModbusDevicePrivate<QModbusDevice, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusDevice(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusDeviceWrapper(*Private(args), args)
			{
			}
			ModbusDevice(QModbusDevice* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusDeviceWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusDevice(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusDeviceWrapper(isolate, tpl) {}
			ModbusDevice(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusDeviceWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusDevice"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
