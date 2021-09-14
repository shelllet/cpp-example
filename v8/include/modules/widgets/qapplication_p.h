#pragma once
#include "core/qcoreapplication_p.h"
namespace shelllet {
	namespace widgets {
		using namespace core;

		template<typename T, bool C>
		class QApplicationPrivate : public QCoreApplicationPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QApplicationPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QCoreApplicationPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}