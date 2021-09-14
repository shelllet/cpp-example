#pragma once
#include "framework.h"
#include <QNetworkDatagram>

namespace shelllet {
	namespace network {
		template <typename T, typename U, bool> class QNetworkDatagramPrivate;
		template <typename T, typename U, bool C>
		class QNetworkDatagramWrapper :public core::ObjectWrapper<T, U, C> {
		public:
			template<bool M>
			QNetworkDatagramWrapper(QNetworkDatagramPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args)
			{
			}
			QNetworkDatagramWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QNetworkDatagramWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "data", v8::FunctionTemplate::New(isolate, Data));
			}

		private:

			static void Data(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QNetworkDatagramWrapper<T, U, C>>(args.This());
					v8::Local<v8::ArrayBuffer> array_buffer;
					{
						QByteArray buffer = p->d_func()->data();
						array_buffer = v8::ArrayBuffer::New(isolate, buffer.size());
						std::memcpy(array_buffer->GetContents().Data(), buffer.constData(), buffer.size());
					}
					args.GetReturnValue().Set(v8::Uint8Array::New(array_buffer, 0, array_buffer->ByteLength()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
