#pragma once
#include "core/qobject_wrapper.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool> class QModbusReplyPrivate;
		template<typename T, typename U, bool C>
		class QModbusReplyWrapper : public QObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QModbusReplyWrapper(QModbusReplyPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QModbusReplyWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QModbusReplyWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "error", v8::FunctionTemplate::New(isolate, Error));
				proto->Set(isolate, "errorString", v8::FunctionTemplate::New(isolate, ErrorString));
				proto->Set(isolate, "isFinished", v8::FunctionTemplate::New(isolate, IsFinished));
				proto->Set(isolate, "rawResult", v8::FunctionTemplate::New(isolate, RawResult));
				proto->Set(isolate, "result", v8::FunctionTemplate::New(isolate, Result));
				proto->Set(isolate, "serverAddress", v8::FunctionTemplate::New(isolate, ServerAddress));
				proto->Set(isolate, "type", v8::FunctionTemplate::New(isolate, Type));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "errorOccurred"), nullptr, ErrorOccurred);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "finished"), nullptr, Finished);
			}

		protected:
			static void Error(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set(static_cast<int>((*self)->error()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorString(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, (*self)->errorString().toUtf8().constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set((*self)->isFinished());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RawResult(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					//	QModbusResponse t = (*self)->rawResult();
					//	args.GetReturnValue().Set(ModbusResponse::New(isolate, ))
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Result(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(ModbusDataUnit::New(isolate, v8::External::New(isolate, &(*self)->result())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ServerAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(v8::Int32::New(isolate, (*self)->serverAddress()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Type(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(static_cast<int>((*self)->type()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorOccurred(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent = std::make_shared<v8::Global<v8::Function>>(isolate, v8::Local<v8::Function>::Cast(value));
						QObject::connect(*self, &QModbusReply::errorOccurred, [isolate, weakPersistent](QModbusDevice::Error error) {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, static_cast<int>(error)) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &QModbusReply::errorOccurred, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Finished(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QModbusReplyWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent = std::make_shared<v8::Global<v8::Function>>(isolate, v8::Local<v8::Function>::Cast(value));
						QObject::connect(*self, &QModbusReply::finished, [isolate, weakPersistent]() {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &QModbusReply::finished, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}