#pragma once
namespace shelllet {
	namespace core {
		template<typename T, bool> class QCoreApplicationPrivate;
		template<typename T, typename U, bool C>
		class QCoreApplicationWrapper : public QObjectWrapper<T, U, C>
		{
		public:

			template <bool M>
			QCoreApplicationWrapper(QCoreApplicationPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QCoreApplicationWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {
				tpl->Set(isolate, "quit", v8::FunctionTemplate::New(isolate, Quit));
			}
			QCoreApplicationWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
			}

		protected:
			static void Quit(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					v8::Unlocker unlocker(isolate);
					QCoreApplication::quit();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}