#pragma once

namespace shelllet {
	namespace random {
		template<typename T, bool> class UniformIntDistributionPrivate;
		template<typename T, typename U, bool C>
		class UniformIntDistributionWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			UniformIntDistributionWrapper(UniformIntDistributionPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			UniformIntDistributionWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			UniformIntDistributionWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
			}

		protected:
		};
	}
}
