#pragma once
#include "framework.h"
#include <random>
#include "uniformintdistribution_p.h"
#include "uniformintdistribution_wrapper.h"
namespace shelllet {
	namespace random {
		class UniformIntDistribution : public UniformIntDistributionWrapper<std::uniform_int_distribution<>, UniformIntDistribution, true>
		{
		public:
			using ReturnType = UniformIntDistributionPrivate<std::uniform_int_distribution<>, true>;
			using ReturnType2 = UniformIntDistributionPrivate<std::uniform_int_distribution<>, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			UniformIntDistribution(const v8::FunctionCallbackInfo<v8::Value>& args) : UniformIntDistributionWrapper(*Private(args), args) {
			}
			UniformIntDistribution(std::uniform_int_distribution<>* p, const v8::FunctionCallbackInfo<v8::Value>& args) : UniformIntDistributionWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			UniformIntDistribution(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : UniformIntDistributionWrapper(isolate, tpl) {}
			UniformIntDistribution(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : UniformIntDistributionWrapper(isolate, proto)
			{}
			static const char* Name() { return "UniformIntDistribution"; }
		public:
		};
	}
}
