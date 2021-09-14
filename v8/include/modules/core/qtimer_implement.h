#pragma once
#include "framework.h"
#include <qtimer.h>
#include "qtimer_p.h"
#include "qtimer_wrapper.h"

namespace shelllet {
	namespace core {
		class Timer : public QTimerWrapper<QTimer, Timer, true>
		{
		public:
			using ReturnType = QTimerPrivate<QTimer, true>;
			using ReturnType2 = QTimerPrivate<QTimer, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			Timer(const v8::FunctionCallbackInfo<v8::Value>& args) :QTimerWrapper(*Private(args), args)
			{
			}
			Timer(QTimer* p, const v8::FunctionCallbackInfo<v8::Value>& args) :QTimerWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Timer(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QTimerWrapper(isolate, tpl) {
				tpl->Set(isolate, "singleShot", v8::FunctionTemplate::New(isolate, SingleShot));
			}
			Timer(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QTimerWrapper(isolate, proto)
			{
			}
		public:
			static const char* Name() { return "Timer"; }
		protected:
			void toString(std::stringstream& ss) const {}
		protected:
			static void SingleShot(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
