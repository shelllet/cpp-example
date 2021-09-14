#pragma once
#include "core/qsize_implement.h"

namespace shelllet {
	using namespace core;
	namespace widgets {
		template<typename T, bool> class WidgetPrivate;
		template<typename T, typename U, bool C>
		class WidgetWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			WidgetWrapper(WidgetPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			WidgetWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			WidgetWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "show", v8::FunctionTemplate::New(isolate, Show));
				proto->Set(isolate, "resize", v8::FunctionTemplate::New(isolate, Resize));
			}

		protected:
			static void Show(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<WidgetWrapper<T, U, C>>(args.This());
					if (!p)
						return;
					(*p)->show();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void Resize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<WidgetWrapper<T, U, C>>(args.This());
					if (!p)
						return;
					auto* value = Size::From(args[0]);
					if (!value) {
						throw std::invalid_argument("#! require `size` object.");
					}
					(*p)->resize((*value)->width(), (*value)->height());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}