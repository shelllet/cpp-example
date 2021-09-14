#pragma once
#include "interpreter/timer_resource.h"
#include "interpreter/global/global.h"
#include "interpreter/global/global_p.h"
#include "interpreter/global/global_wrapper.h"
#include <boost/algorithm/string/predicate.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/algorithm/string/join.hpp>

namespace shelllet {
	using namespace resource;
	namespace global {
		class Global :public MyGlobalWrapper<MyGlobal, Global, false> {
		public:
			using ReturnType = MyGlobalPrivate<MyGlobal, true>;
			using ReturnType2 = MyGlobalPrivate<MyGlobal, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			Global(const v8::FunctionCallbackInfo<v8::Value>& args) : MyGlobalWrapper(*Private(args), args) {
			}
			Global(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : MyGlobalWrapper(isolate, tpl)
			{}
			Global(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : MyGlobalWrapper(isolate, proto)
			{}

		public:
			static const char* Name() { return "global"; }
		};
	}
}
