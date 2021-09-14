#pragma once
#include "core/qobject_p.h"
namespace shelllet {
	namespace widgets {
		template<typename T, bool C>
		class QSystemTrayIconPrivate : public QObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QSystemTrayIconPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
