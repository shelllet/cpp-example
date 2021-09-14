#pragma once
#include "qmodbusclient_p.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusTcpClientPrivate : public QModbusClientPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusTcpClientPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QModbusClientPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		protected:
		};
	}
}
