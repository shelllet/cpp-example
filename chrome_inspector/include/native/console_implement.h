#pragma once
#include "framework.h"
#include <boost/algorithm/string/join.hpp>
#include "console.h"
#include "console_p.h"
#include "console_wrapper.h"

namespace shelllet {
	namespace global {
		class Console : public MyConsoleWrapper<MyConsole, Console, false>
		{
		public:
			using ReturnType = MyConsolePrivate<MyConsole, true>;
			using ReturnType2 = MyConsolePrivate<MyConsole, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			Console(const v8::FunctionCallbackInfo<v8::Value>& args) : MyConsoleWrapper(*Private(args), args)
			{
			}
			Console(MyConsole* p, const v8::FunctionCallbackInfo<v8::Value>& args) : MyConsoleWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Console(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : MyConsoleWrapper(isolate, tpl)
			{}
			
			Console(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : MyConsoleWrapper(isolate, proto)
			{}

			static const char* Name() { return "console"; }
		public:
		};
	}
}
