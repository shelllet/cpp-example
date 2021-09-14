#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, typename U, bool C>
		class MatWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			MatWrapper(MatPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}

			MatWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			MatWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
			}

		protected:
		};
	}
}
