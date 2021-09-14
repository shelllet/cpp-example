#pragma once
#include "framework.h"
#include <QSerialPortInfo>
#include "device_module.h"
#include "qstring_implement.h"
#include "qhostaddress_implement.h"
#include "qserialportinfo_p.h"
#include "qserialportinfo_wrapper.h"

namespace shelllet {
	namespace device {
		class SerialPortInfo : public QSerialPortInfoWrapper<QSerialPortInfo, SerialPortInfo, true>
		{
		public:
			SerialPortInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
			SerialPortInfo(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl);

			static const char* Name();
		};
	}
}
