#pragma once
#include "framework.h"
#include <qeventloop.h>
#include "qeventloop_p.h"
#include "qeventloop_wrapper.h"

namespace shelllet {
	namespace core {
		class EventLoop : public virtual QEventLoopWrapper<QEventLoop, EventLoop, true>
		{
			using ReturnType = QEventLoopPrivate<QEventLoop, true>;
			using ReturnType2 = QEventLoopPrivate<QEventLoop, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			EventLoop(const v8::FunctionCallbackInfo<v8::Value>& args) : QEventLoopWrapper(*Private(args), args)
			{
			}
			EventLoop(QEventLoop* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QEventLoopWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			EventLoop(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QEventLoopWrapper(isolate, tpl)
			{
			}
			EventLoop(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QEventLoopWrapper(isolate, proto)
			{
			}

		public:
			static const char* Name() {
				return "QEventLoop";
			}
		};
	}
}
