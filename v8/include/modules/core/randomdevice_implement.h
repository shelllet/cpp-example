#pragma once
#include "framework.h"
#include <random>
#include "randomdevice_p.h"
#include "randomdevice_wrapper.h"
namespace shelllet {
	namespace random {
		class RandomDevice : public RandomDeviceWrapper<std::random_device, RandomDevice, true>
		{
		public:
			using ReturnType = RandomDevicePrivate<std::random_device, true>;
			using ReturnType2 = RandomDevicePrivate<std::random_device, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			RandomDevice(const v8::FunctionCallbackInfo<v8::Value>& args) : RandomDeviceWrapper(*Private(args), args) {
			}
			RandomDevice(std::random_device* p, const v8::FunctionCallbackInfo<v8::Value>& args) : RandomDeviceWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			RandomDevice(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : RandomDeviceWrapper(isolate, tpl) {}
			RandomDevice(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : RandomDeviceWrapper(isolate, proto)
			{
			}
			static const char* Name() { return "RandomDevice"; }
		public:
		};
	}
}
