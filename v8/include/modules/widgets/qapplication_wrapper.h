#pragma once
#include "core/qcoreapplication_wrapper.h"
namespace shelllet {
	namespace widgets {
		using namespace core;
		template<typename T, bool> class QApplicationPrivate;
		template<typename T, typename U, bool C>
		class QApplicationWrapper : public QCoreApplicationWrapper<T, U, C>
		{
		public:

			template<bool M>
			QApplicationWrapper(QApplicationPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QCoreApplicationWrapper(d, args) {
			}
			QApplicationWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QCoreApplicationWrapper(isolate, tpl) {}
			QApplicationWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QCoreApplicationWrapper(isolate, proto)
			{
			}

		protected:
		};
	}
}
