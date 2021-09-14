#pragma once
#include "framework.h"
#include <QWebSocket>
#include "qobject_wrapper.h"

namespace shelllet {
	namespace network {
		template<typename T, bool> class QWebSocketPrivate;
		template<typename T, typename U, bool C>
		class QWebSocketWrapper : public core::QObjectWrapper<T, U, C> {
		public:
			template<bool M>
			QWebSocketWrapper(QWebSocketPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args)
			{
			}
			QWebSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QWebSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "open", v8::FunctionTemplate::New(isolate, Open));
				tpl->PrototypeTemplate()->Set(isolate, "sendTextMessage", v8::FunctionTemplate::New(isolate, SendTextMessage));
				tpl->PrototypeTemplate()->Set(isolate, "close", v8::FunctionTemplate::New(isolate, Close));
				//tpl->PrototypeTemplate()->Set(isolate, "receive", v8::FunctionTemplate::New(isolate, Receive));
				//tpl->PrototypeTemplate()->Set(isolate, "exit", v8::FunctionTemplate::New(isolate, Exit));
				//tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "connectTimeOut"), nullptr, SetConnectTimeOut);
			}

		private:
			static void Open(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() == 0 || !args[0]->IsString()) {
						qCCritical(shelllet_network) << "#no valid argument for open";
						return;
					}
					v8::String::Utf8Value address{ isolate, args[0] };

					auto* p = convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
					p->socket_->open(QUrl(*address));
				}
				V8_CREATE_LOCAL_CONTEXT_END

					//if (async) {
					//	signal = std::make_shared<boost::signals2::signal<void(const std::unique_ptr<boost::system::system_error>&)>>();

					//	auto resolver = v8::Promise::Resolver::New(isolate->GetCurrentContext()).ToLocalChecked();
					//	auto holder = Holder::newHolder(isolate, resolver);
					//	args.GetReturnValue().Set(resolver->GetPromise());
					//	signal->connect([holder](const std::unique_ptr<boost::system::system_error>& err) {
					//		v8::Locker locker(holder->isolate);
					//		v8::Isolate::Scope scope(holder->isolate);
					//		v8::HandleScope handle_scope(holder->isolate);

					//		if (err)
					//		{
					//			//THROW_EXCEPTION_VAR(holder->isolate, err->what());
					//			holder->resolver.Get(holder->isolate)->Reject(holder->isolate->GetCurrentContext(), v8::False(holder->isolate));
					//			// v8::Isolate::GetCurrent()->RunMicrotasks();
					//			return;
					//		}
					//		holder->resolver.Get(holder->isolate)->Resolve(holder->isolate->GetCurrentContext(), v8::True(holder->isolate));
					//		v8::Isolate::GetCurrent()->RunMicrotasks();
					//		});
					//}

					//async ? client->connect(*address, port, target, signal) : client->connect(*address, port, target);
			}
			static void SendTextMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				//v8::Isolate* isolate = args.GetIsolate();
				//v8::Locker locker(isolate);

				//if (args.Length() < 1) {
				//	//	THROW_EXCEPTION_VAR(isolate, CONTEXT_CAST(isolate)->getLanguageText("plugin.l1").c_str());
				//	return;
				//}

				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() == 0 || !args[0]->IsString()) {
						qCCritical(shelllet_network) << "#no valid argument for open";
						return;
					}

					v8::String::Utf8Value value{ isolate, args[0] };

					auto* p = convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
					p->socket_->sendTextMessage(*value);
				}

				//LOG_INFO(kMainModuleName) << "boost::this_thread::interruption_enabled: " << boost::this_thread::interruption_enabled() << std::endl;
				//boost::this_thread::interruption_point();

				//WebSocket* client =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
				////bool async =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This())->async_;
				//if (!client) {
				//	return;
				//}
				//std::shared_ptr<boost::signals2::signal<void(const std::unique_ptr<boost::system::system_error>&)>> signal;

				//if (client->async_) {
				//	auto resolver = v8::Promise::Resolver::New(isolate->GetCurrentContext()).ToLocalChecked();
				//	args.GetReturnValue().Set(resolver->GetPromise());

				//	signal = std::make_shared<boost::signals2::signal<void(const std::unique_ptr<boost::system::system_error>&)>>();
				//	auto holder = Holder::newHolder(isolate, resolver);

				//	signal->connect([holder](const std::unique_ptr<boost::system::system_error>& err) {
				//		v8::Locker locker(holder->isolate);

				//		if (err)
				//		{
				//			holder->resolver.Get(holder->isolate)->Reject(holder->isolate->GetCurrentContext(), v8::False(holder->isolate));
				//			return;
				//		}
				//		else {
				//			holder->resolver.Get(holder->isolate)->Resolve(holder->isolate->GetCurrentContext(), v8::True(holder->isolate));
				//			v8::Isolate::GetCurrent()->RunMicrotasks();
				//		}
				//		});
				//}

				//if (args[0]->IsString()) {
				//	v8::String::Utf8Value value{ isolate, args[0] };
				//	//std::string string = *value;
				//	client->buffer_ = *value;
				//	try
				//	{
				//		client->async_ ? client->send(boost::asio::buffer(client->buffer_), signal) : client->send(boost::asio::buffer(client->buffer_));
				//	}
				//	catch (const std::exception & err)
				//	{
				//		LOG_ERROR(kMainModuleName) << err.what() << std::endl;
				//	}
				//}
				//else if (args[0]->IsUint8Array()) {
				//	v8::Local<v8::Uint8Array> uint8_array = v8::Local<v8::Uint8Array>::Cast(args[0]);

				//	boost::beast::flat_buffer buffer(uint8_array->Length());

				//	uint8_array->CopyContents(buffer.data().data(), uint8_array->Length());

				//	client->async_ ? client->send(buffer.cdata(), signal) : client->send(buffer.cdata());
				//}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				/*v8::Isolate* isolate = args.GetIsolate();
				v8::Locker locker(isolate);

				bool async =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This())->async_;
				std::shared_ptr<boost::signals2::signal<void()>> signal;

				if (async) {
					auto resolver = v8::Promise::Resolver::New(isolate->GetCurrentContext()).ToLocalChecked();
					args.GetReturnValue().Set(resolver->GetPromise());

					signal = std::make_shared<boost::signals2::signal<void()>>();
					auto holder = Holder::newHolder(isolate, resolver);

					signal->connect([holder] {
						v8::Locker locker(holder->isolate);
						holder->resolver.Get(holder->isolate)->Resolve(holder->isolate->GetCurrentContext(), v8::True(holder->isolate));
						v8::Isolate::GetCurrent()->RunMicrotasks();
						});
				}*/
				//WebSocketClient* client =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
				//async ? client->close(signal) : client->close();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
					p->socket_->close();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Receive(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				/*v8::Isolate* isolate = args.GetIsolate();
				v8::Locker locker(isolate);

				bool async =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This())->async_;
				std::shared_ptr<boost::signals2::signal<void(boost::beast::flat_buffer&, const std::unique_ptr<boost::system::system_error>&)>> signal;
				WebSocketClient* websocket =  convert::Object::UnWrap<QWebSocketWrapper<T, U, C>>(args.This());
				if (async) {
					auto resolver = v8::Promise::Resolver::New(isolate->GetCurrentContext()).ToLocalChecked();
					args.GetReturnValue().Set(resolver->GetPromise());

					signal = std::make_shared<boost::signals2::signal<void(boost::beast::flat_buffer&, const std::unique_ptr<boost::system::system_error>&)>>();
					auto holder = Holder::newHolder(isolate, resolver);

					signal->connect([holder, websocket](boost::beast::flat_buffer& buffer, const std::unique_ptr<boost::system::system_error>& err) {
						v8::Locker locker(holder->isolate);

						if (err)
						{
							holder->resolver.Get(holder->isolate)->Reject(holder->isolate->GetCurrentContext(), v8::False(holder->isolate));
						}
						else {
							if (websocket->isText()) {
								holder->resolver.Get(holder->isolate)->Resolve(holder->isolate->GetCurrentContext(),
									v8::convert::String::NewFromUtf8(holder->isolate, static_cast<const char*>(buffer.data().data()),
										v8::NewStringType::kNormal,
										static_cast<int>(buffer.size())).ToLocalChecked());
								v8::Isolate::GetCurrent()->RunMicrotasks();
							}
							else {
								v8::Local<v8::ArrayBuffer> array_buffer = v8::ArrayBuffer::New(holder->isolate, buffer.data().data(), buffer.size());
								v8::Local<v8::Uint8Array> array = v8::Uint8Array::New(array_buffer, 0, buffer.size());
								holder->resolver.Get(holder->isolate)->Resolve(holder->isolate->GetCurrentContext(), array);
								v8::Isolate::GetCurrent()->RunMicrotasks();
							}
						}
						});
				}
				boost::beast::flat_buffer buffer;

				async ? websocket->receive(signal) : websocket->receive(buffer);

				if (!async) {
					if (websocket->isText()) {
						args.GetReturnValue().Set(convert::String::New(isolate, static_cast<const char*>(buffer.data().data()), v8::NewStringType::kNormal, static_cast<int>(buffer.size())));
					}
					else {
						v8::Local<v8::ArrayBuffer> array_buffer = v8::ArrayBuffer::New(isolate, buffer.data().data(), buffer.size());
						args.GetReturnValue().Set(v8::Uint8Array::New(array_buffer, 0, buffer.size()));
					}
				}*/
			}

		private:
			QWebSocket* socket_;
		};
	}
}
