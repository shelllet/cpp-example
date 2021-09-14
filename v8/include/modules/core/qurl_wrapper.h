#pragma once

namespace shelllet {
	namespace core {
		template<typename T, bool> class QUrlPrivate;
		template<typename T, typename U, bool C>
		class QUrlWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			QUrlWrapper(QUrlPrivate<T, C>& d) : ObjectWrapper(d) {
			}
			template<bool M>
			QUrlWrapper(QUrlPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QUrlWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl)
			{
				tpl->Set(isolate, "fromUserInput", v8::FunctionTemplate::New(isolate, FromUserInput));
			}
			QUrlWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "port", v8::FunctionTemplate::New(isolate, Port));
				proto->Set(isolate, "host", v8::FunctionTemplate::New(isolate, Host));
			}

		protected:
			static void Port(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QUrlWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error("# invalid object.");
					args.GetReturnValue().Set((*p)->port());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void Host(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QUrlWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error("# invalid object.");
					args.GetReturnValue().Set(V8_NEW_WSTRING_VAR(isolate, (*p)->host().toStdWString().c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void FromUserInput(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					QString userInput = ToString({ isolate, args[0] });
					args.GetReturnValue().Set(Url::New(isolate, v8::External::New(isolate, &QUrl::fromUserInput(userInput))));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}