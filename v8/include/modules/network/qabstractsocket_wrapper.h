#pragma once
#include "framework.h"
#include <QAbstractSocket>
#include <QNetworkProxy>
#include "qiodevice_wrapper.h"
#include "qhostaddress_implement.h"
namespace shelllet {
	namespace network {
		template<typename T, bool> class QAbstractSocketPrivate;
		template<typename T, typename U, bool C>
		class QAbstractSocketWrapper : public core::QIODeviceWrapper<T, U, C> {
		public:
			template<bool M>
			QAbstractSocketWrapper(QAbstractSocketPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QIODeviceWrapper(d, args)
			{
			}
			QAbstractSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QIODeviceWrapper(isolate, tpl) {}
			QAbstractSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QIODeviceWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "abort", v8::FunctionTemplate::New(isolate, Abort));
				tpl->PrototypeTemplate()->Set(isolate, "bind", v8::FunctionTemplate::New(isolate, Bind));
				tpl->PrototypeTemplate()->Set(isolate, "connectToHost", v8::FunctionTemplate::New(isolate, ConnectToHost));
				tpl->PrototypeTemplate()->Set(isolate, "disconnectFromHost", v8::FunctionTemplate::New(isolate, DisconnectFromHost));
				tpl->PrototypeTemplate()->Set(isolate, "error", v8::FunctionTemplate::New(isolate, Error));
				tpl->PrototypeTemplate()->Set(isolate, "flush", v8::FunctionTemplate::New(isolate, Flush));
				tpl->PrototypeTemplate()->Set(isolate, "isValid", v8::FunctionTemplate::New(isolate, IsValid));
				tpl->PrototypeTemplate()->Set(isolate, "localAddress", v8::FunctionTemplate::New(isolate, LocalAddress));
				tpl->PrototypeTemplate()->Set(isolate, "localPort", v8::FunctionTemplate::New(isolate, LocalPort));
				tpl->PrototypeTemplate()->Set(isolate, "peerAddress", v8::FunctionTemplate::New(isolate, PeerAddress));
				tpl->PrototypeTemplate()->Set(isolate, "peerName", v8::FunctionTemplate::New(isolate, PeerName));
				tpl->PrototypeTemplate()->Set(isolate, "peerPort", v8::FunctionTemplate::New(isolate, PeerPort));
				tpl->PrototypeTemplate()->Set(isolate, "resume", v8::FunctionTemplate::New(isolate, Resume));
				tpl->PrototypeTemplate()->Set(isolate, "socketType", v8::FunctionTemplate::New(isolate, SocketType));
				tpl->PrototypeTemplate()->Set(isolate, "state", v8::FunctionTemplate::New(isolate, State));
				tpl->PrototypeTemplate()->Set(isolate, "waitForConnected", v8::FunctionTemplate::New(isolate, WaitForConnected));
				tpl->PrototypeTemplate()->Set(isolate, "waitForDisconnected", v8::FunctionTemplate::New(isolate, WaitForDisconnected));
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "connected"), nullptr, SetConnected);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "pauseMode"), PauseMode, SetPauseMode);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "protocolTag"), ProtocolTag, SetProtocolTag);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "proxy"), Proxy, SetProxy);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "readBufferSize"), ReadBufferSize, SetReadBufferSize);
				{
					v8::Local<v8::ObjectTemplate> socket_type = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(socket_type, isolate, QAbstractSocket, SocketType, TcpSocket);
					V8_CREATE_ENUM_SYMBOL(socket_type, isolate, QAbstractSocket, SocketType, UdpSocket);
					V8_CREATE_ENUM_SYMBOL(socket_type, isolate, QAbstractSocket, SocketType, SctpSocket);
					V8_CREATE_ENUM_SYMBOL(socket_type, isolate, QAbstractSocket, SocketType, UnknownSocketType);

					tpl->Set(isolate, "Type", socket_type);

					v8::Local<v8::ObjectTemplate> network_layer_protocol = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(network_layer_protocol, isolate, QAbstractSocket, NetworkLayerProtocol, IPv4Protocol);
					V8_CREATE_ENUM_SYMBOL(network_layer_protocol, isolate, QAbstractSocket, NetworkLayerProtocol, IPv6Protocol);
					V8_CREATE_ENUM_SYMBOL(network_layer_protocol, isolate, QAbstractSocket, NetworkLayerProtocol, AnyIPProtocol);
					V8_CREATE_ENUM_SYMBOL(network_layer_protocol, isolate, QAbstractSocket, NetworkLayerProtocol, UnknownNetworkLayerProtocol);

					tpl->Set(isolate, "Protocol", network_layer_protocol);

					v8::Local<v8::ObjectTemplate> socket_error = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ConnectionRefusedError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, RemoteHostClosedError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, HostNotFoundError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SocketAccessError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SocketResourceError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SocketTimeoutError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, DatagramTooLargeError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, NetworkError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, AddressInUseError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SocketAddressNotAvailableError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, UnsupportedSocketOperationError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, UnfinishedSocketOperationError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyAuthenticationRequiredError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SslHandshakeFailedError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyConnectionRefusedError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyConnectionClosedError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyConnectionTimeoutError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyNotFoundError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, ProxyProtocolError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, OperationError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SslInternalError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, SslInvalidUserDataError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, TemporaryError);
					V8_CREATE_ENUM_SYMBOL(socket_error, isolate, QAbstractSocket, SocketError, UnknownSocketError);

					tpl->Set(isolate, "Error", socket_error);

					v8::Local<v8::ObjectTemplate> socket_state = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, UnconnectedState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, HostLookupState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, ConnectingState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, ConnectedState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, BoundState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, ListeningState);
					V8_CREATE_ENUM_SYMBOL(socket_state, isolate, QAbstractSocket, SocketState, ClosingState);

					tpl->Set(isolate, "State", socket_state);

					v8::Local<v8::ObjectTemplate> socket_option = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, LowDelayOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, KeepAliveOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, MulticastTtlOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, MulticastLoopbackOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, TypeOfServiceOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, SendBufferSizeSocketOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, ReceiveBufferSizeSocketOption);
					V8_CREATE_ENUM_SYMBOL(socket_option, isolate, QAbstractSocket, SocketOption, PathMtuSocketOption);

					tpl->Set(isolate, "Option", socket_option);

					v8::Local<v8::ObjectTemplate> bind_flag = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(bind_flag, isolate, QAbstractSocket, BindFlag, DefaultForPlatform);
					V8_CREATE_ENUM_SYMBOL(bind_flag, isolate, QAbstractSocket, BindFlag, ShareAddress);
					V8_CREATE_ENUM_SYMBOL(bind_flag, isolate, QAbstractSocket, BindFlag, DontShareAddress);
					V8_CREATE_ENUM_SYMBOL(bind_flag, isolate, QAbstractSocket, BindFlag, ReuseAddressHint);

					tpl->Set(isolate, "BindFlag", bind_flag);

					v8::Local<v8::ObjectTemplate> pause_mode = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(pause_mode, isolate, QAbstractSocket, PauseMode, PauseNever);
					V8_CREATE_ENUM_SYMBOL(pause_mode, isolate, QAbstractSocket, PauseMode, PauseOnSslErrors);

					tpl->Set(isolate, "PauseMode", pause_mode);
				}
			}

		private:

			static void Resume(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->resume();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PauseMode(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(p->d_func()->pauseMode());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetPauseMode(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					int m = value->Int32Value(context).FromJust();

					p->d_func()->setPauseMode(static_cast<QAbstractSocket::PauseModes>(m));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetConnected(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());

					v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
					QSharedPointer<v8::Global<v8::Function>>weak_persistent = QSharedPointer<v8::Global<v8::Function>>::create(isolate, f);

					QObject::connect(p->d_func(), &T::connected, [weak_persistent]() {
						v8::Isolate* isolate = v8::Isolate::GetCurrent();
						V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
						{
							v8::TryCatch try_catch(isolate);
							weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
							if (try_catch.HasCaught()) {
								qCCritical(shelllet_network) << try_catch.Exception();
							}
						}
						});
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			//
			//void shelllet::network::AbstractSocket::Connect(const v8::FunctionCallbackInfo<v8::Value>& args)
			//{
			//	V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			//	{
			//		filesystem::IODevice::Connect(args);
			//
			//		if (args.Length() > 0 && args[0]->IsString()) {
			//			auto* p = UnWrap(args.This());
			//			v8::String::Utf8Value signal(isolate, args[0]);
			//
			//			if (strcmp(*signal, "connected") == 0) {
			//				if (args.Length() < 2 || !args[1]->IsFunction()) {
			//					return;
			//				}
			//
			//				CopyablePersistent<v8::Function> function_callback(isolate, v8::Local<v8::Function>::Cast(args[1]));
			//
			//				QMetaObject::Connection conn = QObject::connect(dynamic_cast<QAbstractSocket*>(p), &QAbstractSocket::connected, [isolate, function_callback]() {
			//					V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO_2(isolate)
			//					{
			//						v8::TryCatch try_catch(isolate);
			//						function_callback.Get(isolate)->Call(context, context->Global(), 0, {});
			//						if (try_catch.HasCaught()) {
			//							qCCritical(shelllet_network) << try_catch.Exception();
			//						}
			//					}
			//					});
			//
			//				p->d_func()->push_connection("connected", conn, function_callback);
			//			}
			//
			//			else if (strcmp(*signal, "disconnected") == 0) {
			//				if (args.Length() < 2 || !args[1]->IsFunction()) {
			//					return;
			//				}
			//
			//				v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> function_callback(isolate, v8::Local<v8::Function>::Cast(args[1]));
			//
			//				QMetaObject::Connection conn = QObject::connect(dynamic_cast<QAbstractSocket*>(p), &QAbstractSocket::disconnected, [isolate, function_callback]() {
			//					V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO_2(isolate)
			//					{
			//						function_callback.Get(isolate)->Call(context, context->Global(), 0, {});
			//					}
			//					});
			//
			//				p->d_func()->push_connection("disconnected", conn, function_callback);
			//			}
			//
			//			else if (strcmp(*signal, "stateChanged") == 0) {
			//				if (args.Length() < 2 || !args[1]->IsFunction()) {
			//					return;
			//				}
			//
			//				v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> function_callback(isolate, v8::Local<v8::Function>::Cast(args[1]));
			//
			//				QMetaObject::Connection conn = QObject::connect(dynamic_cast<QAbstractSocket*>(p), &QAbstractSocket::stateChanged, [isolate, function_callback](QAbstractSocket::SocketState socketState) {
			//					V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO_2(isolate)
			//					{
			//						v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, socketState) };
			//						function_callback.Get(isolate)->Call(context, context->Global(), std::size(argv), argv);
			//					}
			//					});
			//
			//				p->d_func()->push_connection("stateChanged", conn, function_callback);
			//			}
			//
			//			else if (strcmp(*signal, "error") == 0) {
			//				if (args.Length() < 2 || !args[1]->IsFunction()) {
			//					return;
			//				}
			//
			//				v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> function_callback(isolate, v8::Local<v8::Function>::Cast(args[1]));
			//
			//				QMetaObject::Connection conn = QObject::connect(dynamic_cast<QAbstractSocket*>(p), qOverload<QAbstractSocket::SocketError>(&QAbstractSocket::error), [isolate, function_callback](QAbstractSocket::SocketError socketError) {
			//					V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO_2(isolate)
			//					{
			//						v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, socketError) };
			//						function_callback.Get(isolate)->Call(context, context->Global(), std::size(argv), argv);
			//					}
			//					});
			//
			//				p->d_func()->push_connection("error", conn, function_callback);
			//			}
			//
			//			else if (strcmp(*signal, "proxyAuthenticationRequired") == 0) {
			//				if (args.Length() < 2 || !args[1]->IsFunction()) {
			//					return;
			//				}
			//			}
			//		}
			//	}
			//}
			//
			//void shelllet::network::AbstractSocket::Disconnect(const v8::FunctionCallbackInfo<v8::Value>& args)
			//{
			//	V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			//	{
			//		common::Object::Disconnect(args);
			//	}
			//}
			static void Bind(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This(), 0);

					QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform;

					if (args.Length() == 0) {
						args.GetReturnValue().Set(p->d_func()->bind());
					}
					else if (args.Length() > 0) {
						if (args[0]->IsSymbol()) {
							auto symbol = v8::Local<v8::Symbol>::Cast(args[0]);
							v8::String::Utf8Value s = { isolate, symbol->Name() };
							QHostAddress address(static_cast<QHostAddress::SpecialAddress>(std::stoi(*s)));
							quint16 port = 0;
							if (args.Length() > 1 && args[1]->IsNumber()) {
								port = args[1]->Int32Value(context).FromJust();
							}
							if (args.Length() > 2 && args[2]->IsSymbol()) {
								auto symbol = v8::Local<v8::Symbol>::Cast(args[0]);
								v8::String::Utf8Value s = { isolate, symbol->Name() };
								mode = static_cast<QAbstractSocket::BindMode>(std::stoi(*s));
							}

							args.GetReturnValue().Set(p->d_func()->bind(address, port, mode));
						}
						else if (args[0]->IsObject()) {
							auto* address = HostAddress::FromValue(isolate, args[0]);
							//QHostAddress address(*(*addr));
							quint16 port = 0;
							if (args.Length() > 1 && args[1]->IsNumber()) {
								port = args[1]->Int32Value(context).FromJust();
							}
							if (args.Length() > 2 && args[2]->IsSymbol()) {
								auto symbol = v8::Local<v8::Symbol>::Cast(args[0]);
								v8::String::Utf8Value s = { isolate, symbol->Name() };
								mode = static_cast<QAbstractSocket::BindMode>(std::stoi(*s));
							}

							args.GetReturnValue().Set(p->d_func()->bind(***address, port, mode));
						}
						else if (args[0]->IsNumber()) {
							quint16 port = args[0]->Int32Value(context).FromJust();
							if (args.Length() > 1 && args[1]->IsSymbol()) {
								auto symbol = v8::Local<v8::Symbol>::Cast(args[0]);
								v8::String::Utf8Value s = { isolate, symbol->Name() };
								mode = static_cast<QAbstractSocket::BindMode>(std::stoi(*s));
							}
							args.GetReturnValue().Set(p->d_func()->bind(port, mode));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ConnectToHost(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					QString host_name;
					QHostAddress address;
					quint16 port;
					if (V8_IsString(args, 0)) {
						host_name = convert::String::To(isolate, args[0]);
					}
					else if (V8_IsObject(args, 0)) {
						HostAddress* p = convert::Object::UnWrap<HostAddress>(args[0]->ToObject(context).ToLocalChecked());
						address = ***p;
					}
					else if (V8_IsNumber(args, 0)) {
						address = static_cast<QHostAddress::SpecialAddress>(isolate, args[0]->Int32Value(context).FromJust());
					}

					if (V8_IsNumber(args, 1)) {
						port = args[1]->Int32Value(context).FromJust();
					}

					QIODevice::OpenMode	openMode = QAbstractSocket::ReadWrite;
					QAbstractSocket::NetworkLayerProtocol protocol = QAbstractSocket::AnyIPProtocol;

					if (V8_IsNumber(args, 2)) {
						openMode = static_cast<QIODevice::OpenMode>(isolate, args[2]->Int32Value(context).FromJust());
					}
					if (V8_IsNumber(args, 3)) {
						protocol = static_cast<QAbstractSocket::NetworkLayerProtocol>(isolate, args[3]->Int32Value(context).FromJust());
					}
					if (!address.isNull())
						p->d_func()->connectToHost(address, port, openMode);
					else if (!host_name.trimmed().isEmpty()) {
						p->d_func()->connectToHost(host_name, port, openMode, protocol);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DisconnectFromHost(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						//	p->d_func()->disconnectFromHost();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isValid();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesAvailable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->bytesAvailable();

						args.GetReturnValue().Set(v8::BigInt::New(isolate, result));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesToWrite(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->bytesToWrite();

						args.GetReturnValue().Set(v8::BigInt::New(isolate, result));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CanReadLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->canReadLine();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LocalPort(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->localPort();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void LocalAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->localAddress();
						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &result) };

						args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "HostAddress", std::size(argv), argv));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PeerPort(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->peerPort();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PeerAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->peerAddress();

						v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &result) };

						args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "HostAddress", std::size(argv), argv));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PeerName(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->peerName();

						args.GetReturnValue().Set(convert::String::New(isolate, qPrintable(result)));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadBufferSize(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(v8::BigInt::New(isolate, p->d_func()->readBufferSize()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetReadBufferSize(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					p->d_func()->setReadBufferSize(value->ToBigInt(context).ToLocalChecked()->Int64Value());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Abort(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->abort();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SocketDescriptor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					args.GetReturnValue().Set(std::int32_t(p->d_func()->socketDescriptor()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetSocketDescriptor(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (args.Length() < 1 || !args[0]->IsNumber())
					{
						return;
					}
					QAbstractSocket::SocketState socket_state = QAbstractSocket::ConnectedState;
					QIODevice::OpenMode open_mode = QAbstractSocket::ReadWrite;
					qintptr socket_descriptor = args[0]->Int32Value(context).FromJust();

					if (args.Length() > 1 && args[1]->IsNumber()) {
						socket_state = static_cast<QAbstractSocket::SocketState>(args[1]->Int32Value(context).FromJust());
					}
					if (args.Length() > 2 && args[2]->IsNumber()) {
						open_mode = static_cast<QIODevice::OpenMode>(args[2]->Int32Value(context).FromJust());
					}

					p->d_func()->setSocketDescriptor(socket_descriptor, socket_state, open_mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetSocketOption(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (args.Length() < 2 || !args[0]->IsNumber() || !args[1]->IsObject()) {
						return;
					}
					QAbstractSocket::SocketOption option = static_cast<QAbstractSocket::SocketOption>(args[0]->Int32Value(context).FromJust());

					auto* v = static_cast<QVariant*>(args.This()->ToObject(context).ToLocalChecked()->GetAlignedPointerFromInternalField(0));
					p->d_func()->setSocketOption(option, *v);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SocketOption(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (args.Length() < 1 || !args[0]->IsNumber()) {
						return;
					}

					auto option = p->d_func()->socketOption(static_cast<QAbstractSocket::SocketOption>(args[0]->Int32Value(context).FromJust()));
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &option) };
					args.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "Variant", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SocketType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->socketType();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void State(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->state();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Error(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->error();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->close();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSequential(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isSequential();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void AtEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->atEnd();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Flush(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->flush();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForConnected(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						int msec = 30000;
						if (args.Length() > 0 && args[0]->IsNumber()) {
							msec = args[0]->Int32Value(context).FromJust();
						}
						args.GetReturnValue().Set(p->d_func()->waitForConnected(msec));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForReadyRead(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						int msec = 30000;
						if (args.Length() > 0 && args[0]->IsNumber()) {
							msec = args[0]->Int32Value(context).FromJust();
						}
						args.GetReturnValue().Set(p->d_func()->waitForReadyRead(msec));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForBytesWritten(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						int msec = 30000;
						if (args.Length() > 0 && args[0]->IsNumber()) {
							msec = args[0]->Int32Value(context).FromJust();
						}
						args.GetReturnValue().Set(p->d_func()->waitForBytesWritten(msec));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForDisconnected(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(args.This());
					if (p)
					{
						int msec = 30000;
						if (args.Length() > 0 && args[0]->IsNumber()) {
							msec = args[0]->Int32Value(context).FromJust();
						}
						args.GetReturnValue().Set(p->d_func()->waitForDisconnected(msec));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetProxy(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					QNetworkProxy* proxy = static_cast<QNetworkProxy*>(value->ToObject(context).ToLocalChecked()->GetAlignedPointerFromInternalField(0));

					p->d_func()->setProxy(*proxy);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Proxy(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());
					v8::Local<v8::Value> argv[] = { v8::External::New(isolate, &p->d_func()->proxy()) };
					info.GetReturnValue().Set(convert::Object::Wrap(isolate, context, "NetworkProxy", std::size(argv), argv));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProtocolTag(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());

					info.GetReturnValue().Set(convert::String::New(isolate, qPrintable(p->d_func()->protocolTag())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetProtocolTag(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QAbstractSocketWrapper<T, U, C>>(info.This());

					v8::String::Utf8Value tag(isolate, value);
					p->d_func()->setProtocolTag(*tag);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
