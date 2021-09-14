#pragma once

namespace shelllet {
	namespace global {
		template<typename T, typename U, bool C>
		class MyConsoleWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			MyConsoleWrapper(MyConsolePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper<T, U, C>(d, args) {
			}
			MyConsoleWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper<T, U, C>(isolate, tpl)
			{
				tpl->Set(isolate, "log", v8::FunctionTemplate::New(isolate, Print));
			}
			MyConsoleWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper<T, U, C>(isolate, proto)
			{
			}

		protected:
			static void Print(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					std::vector<std::wstring> list;
					for (int i = 0; i < args.Length(); i++) {
						list.push_back(ToWString({ isolate, args[i] }));
					}
					std::wcout.imbue(std::locale(std::locale(), "", LC_CTYPE));
					std::wcout << boost::join(list, " ") << std::endl;
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
