#pragma once
#include "framework.h"
#include <QTcpServer>
#include "qobject_wrapper.h"
namespace shelllet {
	namespace network {
		template<typename T, bool> class QTcpServerPrivate;
		template<typename T, typename U, bool C>
		class QTcpServerWrapper : public core::QObjectWrapper<T, U, C> {
		public:
			template<bool M>
			QTcpServerWrapper(QTcpServerPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args)
			{
			}
			QTcpServerWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QTcpServerWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "listen", v8::FunctionTemplate::New(isolate, Listen));
			}

		private:
			static void Listen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
			}
		};
	}
}
