#pragma once

namespace shelllet {
	namespace random {
		template<typename T, bool> class RandomDevicePrivate;
		template<typename T, typename U, bool C>
		class RandomDeviceWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			RandomDeviceWrapper(RandomDevicePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			RandomDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			RandomDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
			}

		protected:
		};
	}
}
