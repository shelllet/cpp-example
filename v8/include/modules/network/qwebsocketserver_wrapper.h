#pragma once
#include "framework.h"
#include <QWebSocketServer>
#include "qobject_wrapper.h"
#include "qhostaddress_implement.h"

namespace shelllet {
	namespace network {
		template<typename T, bool> class QWebSocketServerPrivate;
		template<typename T, typename U, bool C>
		class QWebSocketServerWrapper : public core::QObjectWrapper<T, U, C> {
		public:
			template<bool M>
			QWebSocketServerWrapper(QWebSocketServerPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args)
			{
			}
			QWebSocketServerWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QWebSocketServerWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "close", v8::FunctionTemplate::New(isolate, Close));
				tpl->PrototypeTemplate()->Set(isolate, "listen", v8::FunctionTemplate::New(isolate, Listen));
				tpl->PrototypeTemplate()->Set(isolate, "nextPendingConnection", v8::FunctionTemplate::New(isolate, NextPendingConnection));
			}

		protected:
			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWebSocketServerWrapper<T, U, C>>(args.This());
					p->d_func()->close();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void NextPendingConnection(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWebSocketServerWrapper<T, U, C>>(args.This());
					QWebSocket* socket = p->d_func()->nextPendingConnection();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Listen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWebSocketServerWrapper<T, U, C>>(args.This());
					if (!p)
						return;

					auto* address = HostAddress::FromValue(isolate, args[0]);
					quint16 port = 0;
					if (args[1]->IsNumber()) {
						port = args[1]->Int32Value(context).FromJust();
					}

					args.GetReturnValue().Set(p->d_func()->listen(***address, port));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
