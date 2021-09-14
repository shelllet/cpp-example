#pragma once
#include "framework.h"
#include <QSerialPort>
#include "device_module.h"
#include "qserialport_p.h"
#include "qserialport_wrapper.h"

namespace shelllet {
	namespace device {
		class SerialPort : public QSerialPortWrapper<QSerialPort, SerialPort, true>
		{
		public:
			SerialPort(const v8::FunctionCallbackInfo<v8::Value>& args);
			SerialPort(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

			static const char* Name();

		public:
		};
	}
}
