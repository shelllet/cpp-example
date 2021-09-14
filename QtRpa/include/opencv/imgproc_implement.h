#pragma once
#include "framework.h"
#include <opencv2/imgproc.hpp>
#include "mat_implement.h"
#include "scalar_implement.h"
#include "imgproc_p.h"
#include "imgproc_wrapper.h"
namespace shelllet {
	namespace opencv {
		class __ImgProc {};
		class ImgProc : public ImgProcWrapper<__ImgProc, ImgProc, false>
		{
			using ReturnType = ImgProcPrivate<__ImgProc, true>;
			using ReturnType2 = ImgProcPrivate<__ImgProc, false>;

			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			ImgProc(const v8::FunctionCallbackInfo<v8::Value>& args) : ImgProcWrapper(*Param(args), args)
			{
			}
			ImgProc(__ImgProc* p, const v8::FunctionCallbackInfo<v8::Value>& args) : ImgProcWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ImgProc(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ImgProcWrapper(isolate, tpl)
			{
			}
			ImgProc(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ImgProcWrapper(isolate, proto)
			{
			}
			static const char* Name() { return "cv"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
