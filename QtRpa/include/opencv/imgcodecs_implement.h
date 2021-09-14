#pragma once
#include "framework.h"
#include <opencv2/imgcodecs.hpp>
#include "imgcodecs_p.h"
#include "imgcodecs_wrapper.h"
namespace shelllet {
	namespace opencv {
		class __ImgCodecs {};
		class ImgCodecs : public ImgCodecsWrapper<__ImgCodecs, ImgCodecs, false>
		{
		public:
			using ReturnType = ImgCodecsPrivate<__ImgCodecs, true>;
			using ReturnType2 = ImgCodecsPrivate<__ImgCodecs, false>;

			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			ImgCodecs(const v8::FunctionCallbackInfo<v8::Value>& args) : ImgCodecsWrapper(*Param(args), args)
			{
			}
			ImgCodecs(__ImgCodecs* p, const v8::FunctionCallbackInfo<v8::Value>& args) : ImgCodecsWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}

			ImgCodecs(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ImgCodecsWrapper(isolate, tpl)
			{
			}
			ImgCodecs(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ImgCodecsWrapper(isolate, proto)
			{
			}
			static const char* Name() { return "cv"; }
		protected:
		};
	}
}
