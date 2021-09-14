#pragma once
#include "framework.h"
#include <opencv2/core.hpp>
#include "scalar_p.h"
#include "scalar_wrapper.h"
namespace shelllet {
	namespace opencv {
		class Scalar : public ScalarWrapper<cv::Scalar, Scalar, true>
		{
			using ReturnType = ScalarPrivate<cv::Scalar, true>;
			using ReturnType2 = ScalarPrivate<cv::Scalar, false>;

			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			Scalar(const v8::FunctionCallbackInfo<v8::Value>& args) : ScalarWrapper(*Param(args), args)
			{
			}
			Scalar(cv::Scalar* p, const v8::FunctionCallbackInfo<v8::Value>& args) : ScalarWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Scalar(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ScalarWrapper(isolate, tpl)
			{
			}
			Scalar(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ScalarWrapper(isolate, proto)
			{
			}

			static const char* Name()
			{
				return "Mat";
			}

		protected:
		};
	}
}
