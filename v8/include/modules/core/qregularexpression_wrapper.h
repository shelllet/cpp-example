#pragma once

namespace shelllet {
	namespace core {
		template<typename T, bool> class RegularExpressionPrivate;
		template<typename T, typename U, bool C>
		class RegularExpressionWrapper : public ObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			RegularExpressionWrapper(RegularExpressionPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			RegularExpressionWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			RegularExpressionWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {}

		protected:
		};
	}
}
