#pragma once
#include "framework.h"
#include <opencv2/imgcodecs.hpp>
#include "core_p.h"
#include "core_wrapper.h"
namespace shelllet {
	namespace opencv {
		class __Core {};
		class Core : public CoreWrapper<__Core, Core, false>
		{
		public:
			using ReturnType = CorePrivate<__Core, true>;
			using ReturnType2 = CorePrivate<__Core, false>;

			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			Core(const v8::FunctionCallbackInfo<v8::Value>& args) : CorePrivate(*Param(args), args)
			{
			}
			Core(cv::Mat* p, const v8::FunctionCallbackInfo<v8::Value>& args) : CorePrivate(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Core(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : CorePrivate(isolate, tpl, proto)
			{
			}
			Core(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : CorePrivate(isolate, tpl, proto)
			{
			}
			static const char* Name() { return "cv"; }
		protected:
		};
	}
}
