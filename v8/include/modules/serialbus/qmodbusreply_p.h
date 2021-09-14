#pragma once
#include "core/qobject_p.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusReplyPrivate : public QObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusReplyPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args) ...) {
			}
		};
	}
}
