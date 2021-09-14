#pragma once

namespace shelllet {
	namespace core {
		template<typename T, bool> class QStringPrivate;
		template<typename T, typename U, bool C>
		class QStringWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QStringWrapper(QStringPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}

			QStringWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QStringWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
			}

		protected:
		};
	}
}
