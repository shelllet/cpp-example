#pragma once
#include "framework.h"
#include <QUdpSocket>
#include <QNetworkDatagram>
#include "qabstractsocket_wrapper.h"
#include "qtcpServer_wrapper.h"
#include "qnetworkdatagram_implement.h"

namespace shelllet {
	namespace network {
		template<typename T, bool> class QUdpSocketPrivate;
		template<typename T, typename U, bool C>
		class QUdpSocketWrapper : public QAbstractSocketWrapper<T, U, C> {
		public:
			template<bool M>
			QUdpSocketWrapper(QUdpSocketPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QAbstractSocketWrapper(d, args)
			{
			}
			QUdpSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QAbstractSocketWrapper(isolate, tpl) {}
			QUdpSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QAbstractSocketWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "hasPendingDatagrams", v8::FunctionTemplate::New(isolate, HasPendingDatagrams));
				tpl->PrototypeTemplate()->Set(isolate, "receiveDatagram", v8::FunctionTemplate::New(isolate, ReceiveDatagram));
				tpl->PrototypeTemplate()->Set(isolate, "writeDatagram", v8::FunctionTemplate::New(isolate, WriteDatagram));
			}
			virtual ~QUdpSocketWrapper() {
			}

		private:

			static void HasPendingDatagrams(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QUdpSocketWrapper<T, U, C>>(args.This());

					args.GetReturnValue().Set(p->d_func()->hasPendingDatagrams());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WriteDatagram(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QUdpSocketWrapper<T, U, C>>(args.This());
					if (args.Length() > 0 && args[0]->IsObject()) {
						auto* datagram = NetworkDatagram::FromValue(isolate, args[0]);
						p->d_func()->writeDatagram(***datagram);
					}
					else if (args.Length() > 0 && args[0]->IsUint8Array()) {
						v8::Local<v8::Uint8Array> array = v8::Local<v8::Uint8Array>::Cast(args[0]);
						QByteArray datagram(array->Length(), '\0');
						QHostAddress address;
						quint16 port = 0;
						array->CopyContents(datagram.data(), datagram.length());

						if (args.Length() > 1 && args[1]->IsObject()) {
							auto* p = HostAddress::FromValue(isolate, args[1]);
							address = ***p;
						}
						if (args.Length() > 2 && args[2]->IsNumber()) {
							port = args[2]->NumberValue(context).FromJust();
						}

						if (!address.isNull()) {
							p->d_func()->writeDatagram(datagram, address, port);
						}
					}
					else if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value datagram = { isolate, args[0] };

						QHostAddress address;
						quint16 port = 0;
						if (args.Length() > 1 && args[1]->IsObject()) {
							auto* p = HostAddress::FromValue(isolate, args[1]);
							address = ***p;
							return;
						}
						else if (args.Length() > 1 && args[1]->IsSymbol()) {
							auto symbol = v8::Local<v8::Symbol>::Cast(args[1]);
							v8::String::Utf8Value s = { isolate, symbol->Name() };
							address = static_cast<QHostAddress::SpecialAddress>(std::stoi(*s));
						}
						if (args.Length() > 2 && args[2]->IsNumber()) {
							port = args[2]->NumberValue(context).FromJust();
						}
						if (!address.isNull())
							p->d_func()->writeDatagram(*datagram, datagram.length(), address, port);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReceiveDatagram(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QUdpSocketWrapper<T, U, C>>(args.This());

					QNetworkDatagram datagram = p->d_func()->receiveDatagram();
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &datagram) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "NetworkDatagram", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
