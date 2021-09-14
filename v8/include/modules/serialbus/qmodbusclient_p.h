#pragma once
#include "qmodbusdevice_p.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusClientPrivate : public QModbusDevicePrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusClientPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QModbusDevicePrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		protected:
		};
	}
}
