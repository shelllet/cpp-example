#pragma once
#include "core/qobject_wrapper.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool> class QModbusDevicePrivate;
		template<typename T, typename U, bool C>
		class QModbusDeviceWrapper : public QObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QModbusDeviceWrapper(QModbusDevicePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QModbusDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {
				auto connectionParameter = v8::FunctionTemplate::New(isolate);
				connectionParameter->Set(isolate, "SerialPortNameParameter", v8::Int32::New(isolate, QModbusDevice::SerialPortNameParameter));
				connectionParameter->Set(isolate, "SerialParityParameter", v8::Int32::New(isolate, QModbusDevice::SerialParityParameter));
				connectionParameter->Set(isolate, "SerialBaudRateParameter", v8::Int32::New(isolate, QModbusDevice::SerialBaudRateParameter));
				connectionParameter->Set(isolate, "SerialDataBitsParameter", v8::Int32::New(isolate, QModbusDevice::SerialDataBitsParameter));
				connectionParameter->Set(isolate, "SerialStopBitsParameter", v8::Int32::New(isolate, QModbusDevice::SerialStopBitsParameter));
				connectionParameter->Set(isolate, "NetworkPortParameter", v8::Int32::New(isolate, QModbusDevice::NetworkPortParameter));
				connectionParameter->Set(isolate, "NetworkAddressParameter", v8::Int32::New(isolate, QModbusDevice::NetworkAddressParameter));
				tpl->Set(isolate, "ConnectionParameter", connectionParameter);

				auto error = v8::FunctionTemplate::New(isolate);
				error->Set(isolate, "NoError", v8::Int32::New(isolate, QModbusDevice::NoError));
				error->Set(isolate, "ReadError", v8::Int32::New(isolate, QModbusDevice::ReadError));
				error->Set(isolate, "WriteError", v8::Int32::New(isolate, QModbusDevice::WriteError));
				error->Set(isolate, "ConnectionError", v8::Int32::New(isolate, QModbusDevice::ConnectionError));
				error->Set(isolate, "ConfigurationError", v8::Int32::New(isolate, QModbusDevice::ConfigurationError));
				error->Set(isolate, "TimeoutError", v8::Int32::New(isolate, QModbusDevice::TimeoutError));
				error->Set(isolate, "ProtocolError", v8::Int32::New(isolate, QModbusDevice::ProtocolError));
				error->Set(isolate, "ReplyAbortedError", v8::Int32::New(isolate, QModbusDevice::ReplyAbortedError));
				error->Set(isolate, "UnknownError", v8::Int32::New(isolate, QModbusDevice::UnknownError));
				tpl->Set(isolate, "Error", error);

				auto state = v8::FunctionTemplate::New(isolate);
				state->Set(isolate, "UnconnectedState", v8::Int32::New(isolate, QModbusDevice::UnconnectedState));
				state->Set(isolate, "ConnectingState", v8::Int32::New(isolate, QModbusDevice::ConnectingState));
				state->Set(isolate, "ConnectedState", v8::Int32::New(isolate, QModbusDevice::ConnectedState));
				state->Set(isolate, "ClosingState", v8::Int32::New(isolate, QModbusDevice::ClosingState));
				tpl->Set(isolate, "State", state);
			}
			QModbusDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "setConnectionParameter", v8::FunctionTemplate::New(isolate, SetConnectionParameter));
				proto->Set(isolate, "connectDevice", v8::FunctionTemplate::New(isolate, ConnectDevice));
				proto->Set(isolate, "disconnectDevice", v8::FunctionTemplate::New(isolate, DisconnectDevice));
				proto->Set(isolate, "errorString", v8::FunctionTemplate::New(isolate, ErrorString));
				proto->Set(isolate, "state", v8::FunctionTemplate::New(isolate, State));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "errorOccurred"), nullptr, ErrorOccurred);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "stateChanged"), nullptr, StateChanged);
			}

		protected:
			static void ErrorString(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QModbusDeviceWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, (*p)->errorString().toUtf8().constData()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void ConnectDevice(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QModbusDeviceWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set((*p)->connectDevice());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void DisconnectDevice(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QModbusDeviceWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					(*p)->disconnectDevice();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetConnectionParameter(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QModbusDeviceWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					int parameter = args[0]->Int32Value(context).FromJust();
					QVariant value;
					if (args[1]->IsNumber()) {
						value = args[1]->Int32Value(context).FromJust();
					}
					else {
						value = QString::fromStdString(ToString({ isolate, args[1] }));
					}
					(*p)->setConnectionParameter(parameter, value);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void State(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QModbusDeviceWrapper<T, U, C>>(args.This());
					if (!p)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(v8::Int32::New(isolate, (*p)->state()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorOccurred(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QModbusDeviceWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weak_persistent = std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
							});

						QObject::connect(*self, &QModbusDevice::errorOccurred, [isolate, weak_persistent](QModbusDevice::Error error) {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, error) };
								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &QModbusDevice::errorOccurred, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void StateChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QModbusDeviceWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weak_persistent = std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
							});

						QObject::connect(*self, &QModbusDevice::stateChanged, [isolate, weak_persistent](QModbusDevice::State state) {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, state) };
								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &QModbusDevice::stateChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}