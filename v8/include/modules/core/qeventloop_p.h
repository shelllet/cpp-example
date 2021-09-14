#pragma once
#include "framework.h"
#include "qobject_p.h"

namespace shelllet {
	namespace core {
		template<typename T, bool C>
		class QEventLoopPrivate : public QObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QEventLoopPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}