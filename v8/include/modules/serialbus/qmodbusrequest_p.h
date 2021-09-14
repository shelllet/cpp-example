#pragma once
#include "qmodbuspdu_p.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusRequestPrivate : public QModbusPduPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusRequestPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QModbusPduPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
