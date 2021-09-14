#pragma once
#include "framework.h"
#include <opencv2/opencv.hpp>
#include "mat_p.h"
#include "mat_wrapper.h"
namespace shelllet {
	namespace opencv {
		class Mat : public MatWrapper<cv::Mat, Mat, true>
		{
			using ReturnType = MatPrivate<cv::Mat, true>;
			using ReturnType2 = MatPrivate<cv::Mat, false>;

			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				if (args[0]->IsExternal()) {
					cv::Mat* m = static_cast<cv::Mat*>(args[0].As<v8::External>()->Value());
					if (m) {
						return new ReturnType(args.GetIsolate(), args.This(), *m);
					}
				}
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			Mat(const v8::FunctionCallbackInfo<v8::Value>& args) : MatWrapper(*Param(args), args)
			{
			}
			Mat(cv::Mat* p, const v8::FunctionCallbackInfo<v8::Value>& args) : MatWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Mat(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : MatWrapper(isolate, tpl)
			{
			}
			Mat(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : MatWrapper(isolate, proto)
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
