#pragma once
#include "qiodevice_p.h"

namespace shelllet::device {
	template<typename T, bool C>
	class QSerialPortPrivate : public core::QIODevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QSerialPortPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QIODevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}

		
	};
}
