#pragma once
#include "framework.h"
#include <qcoreapplication.h>
#include "qcoreapplication_p.h"
#include "qcoreapplication_wrapper.h"

namespace shelllet {
	namespace core {
		class CoreApplication : public QCoreApplicationWrapper<QCoreApplication, CoreApplication, true>
		{
		public:
			using ReturnType = QCoreApplicationPrivate<QCoreApplication, true>;
			using ReturnType2 = QCoreApplicationPrivate<QCoreApplication, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This(), __argc, __argv);
			}

			CoreApplication(const v8::FunctionCallbackInfo<v8::Value>& args) :QCoreApplicationWrapper(*Private(args), args)
			{
			}
			CoreApplication(QCoreApplication* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QCoreApplicationWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			CoreApplication(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QCoreApplicationWrapper(isolate, tpl)
			{
				tpl->Set(isolate, "exec", v8::FunctionTemplate::New(isolate, Exec));
			}
			CoreApplication(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QCoreApplicationWrapper(isolate, proto)
			{
			}

			static const char* Name() { return "CoreApplication"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}

			static void Exec(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					v8::Unlocker unlocker(isolate);
					QCoreApplication::exec();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
