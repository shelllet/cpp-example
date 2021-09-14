#pragma once
#include "qwidget_wrapper.h"
namespace shelllet {
	namespace widgets {
		template<typename T, bool> class MainWindowPrivate;
		template<typename T, typename U, bool C>
		class MainWindowWrapper : public WidgetWrapper<T, U, C>
		{
		public:
			template<bool M>
			MainWindowWrapper(MainWindowPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: WidgetWrapper(d, args) {
			}
			MainWindowWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : WidgetWrapper(isolate, tpl) {
				tpl->Set(isolate, "log", v8::FunctionTemplate::New(isolate, Print));
			}
			MainWindowWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : WidgetWrapper(isolate, proto)
			{
			}

		protected:
			static void Print(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}