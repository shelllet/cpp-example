#pragma once
#include "framework.h"
#include <QApplication>
#include "qapplication_p.h"
#include "qapplication_wrapper.h"

namespace shelllet {
	namespace widgets {
		class Application : public QApplicationWrapper<QApplication, Application, true>
		{
		public:
			using ReturnType = QApplicationPrivate<QApplication, true>;
			using ReturnType2 = QApplicationPrivate<QApplication, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This(), __argc, __argv);
			}
			Application(const v8::FunctionCallbackInfo<v8::Value>& args) :QApplicationWrapper(*Private(args), args)
			{
			}
			Application(QApplication* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QApplicationWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Application(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QApplicationWrapper(isolate, tpl) {
				tpl->Set(isolate, "exec", v8::FunctionTemplate::New(isolate, Exec));
			}
			Application(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QApplicationWrapper(isolate, proto)
			{
			}

			static const char* Name() { return "Application"; }
		protected:
			static void Exec(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					v8::Unlocker unlocker(isolate);
					QApplication::exec();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
