#pragma once

namespace shelllet {
	namespace serialbus {
		template<typename T, bool> class QModbusPduPrivate;
		template<typename T, typename U, bool C>
		class QModbusPduWrapper : public ObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			QModbusPduWrapper(QModbusPduPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QModbusPduWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {
				tpl->Set(isolate, "log", v8::FunctionTemplate::New(isolate, Print));
			}
			QModbusPduWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
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
			static void Get(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Set(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}