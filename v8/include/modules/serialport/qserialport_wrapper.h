#pragma once
#include "framework.h"
#include <QSerialPort>
#include "qiodevice_wrapper.h"
#include "qserialportinfo_implement.h"
namespace shelllet {
	namespace device {
		template<typename T, bool> class QSerialPortPrivate;
		template<typename T, typename U, bool C>
		class QSerialPortWrapper : public core::QIODeviceWrapper<T, U, C>
		{
		public:
			template<bool M>
			QSerialPortWrapper(QSerialPortPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QIODeviceWrapper(d, args) {
			}
			QSerialPortWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QIODeviceWrapper(isolate, tpl) {}
			QSerialPortWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QIODeviceWrapper(isolate, proto) {
				{
					/*tpl->Set(isolate, "atEnd", v8::FunctionTemplate::New(isolate, AtEnd));
				tpl->PrototypeTemplate()->Set(isolate, "bytesAvailable", v8::FunctionTemplate::New(isolate, BytesAvailable));
				tpl->PrototypeTemplate()->Set(isolate, "bytesToWrite", v8::FunctionTemplate::New(isolate, BytesToWrite));
				tpl->PrototypeTemplate()->Set(isolate, "canReadLine", v8::FunctionTemplate::New(isolate, CanReadLine));*/
					tpl->PrototypeTemplate()->Set(isolate, "clear", v8::FunctionTemplate::New(isolate, Clear));
					tpl->PrototypeTemplate()->Set(isolate, "clearError", v8::FunctionTemplate::New(isolate, ClearError));
					//tpl->PrototypeTemplate()->Set(isolate, "close", v8::FunctionTemplate::New(isolate, Close));
					tpl->PrototypeTemplate()->Set(isolate, "flush", v8::FunctionTemplate::New(isolate, Flush));
					tpl->PrototypeTemplate()->Set(isolate, "handle", v8::FunctionTemplate::New(isolate, Handle));
					//tpl->PrototypeTemplate()->Set(isolate, "isSequential", v8::FunctionTemplate::New(isolate, IsSequential));
					//tpl->PrototypeTemplate()->Set(isolate, "open", v8::FunctionTemplate::New(isolate, Open));
					tpl->PrototypeTemplate()->Set(isolate, "pinoutSignals", v8::FunctionTemplate::New(isolate, PinoutSignals));
					tpl->PrototypeTemplate()->Set(isolate, "readBufferSize", v8::FunctionTemplate::New(isolate, ReadBufferSize));
					tpl->PrototypeTemplate()->Set(isolate, "setPort", v8::FunctionTemplate::New(isolate, SetPort));
					tpl->PrototypeTemplate()->Set(isolate, "setReadBufferSize", v8::FunctionTemplate::New(isolate, SetReadBufferSize));
					//tpl->PrototypeTemplate()->Set(isolate, "waitForBytesWritten", v8::FunctionTemplate::New(isolate, WaitForBytesWritten));
					//tpl->PrototypeTemplate()->Set(isolate, "waitForReadyRead", v8::FunctionTemplate::New(isolate, WaitForReadyRead));
					tpl->PrototypeTemplate()->Set(isolate, "baudRate", v8::FunctionTemplate::New(isolate, BaudRate));
					tpl->PrototypeTemplate()->Set(isolate, "setBaudRate", v8::FunctionTemplate::New(isolate, SetBaudRate));

					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "portName"), PortName, SetPortName);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "dataBits"), DataBits, SetDataBits);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "parity"), Parity, SetParity);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "stopBits"), StopBits, SetStopBits);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "flowControl"), FlowControl, SetFlowControl);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "dataTerminalReady"), IsDataTerminalReady, SetDataTerminalReady);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "requestToSend"), IsRequestToSend, SetRequestToSend);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "breakEnabled"), IsBreakEnabled, SetBreakEnabled);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "error"), Error, nullptr);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "baudRateChanged"), nullptr, BaudRateChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "breakEnabledChanged"), nullptr, BreakEnabledChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "dataBitsChanged"), nullptr, DataBitsChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "dataTerminalReadyChanged"), nullptr, DataTerminalReadyChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "errorOccurred"), nullptr, ErrorOccurred);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "flowControlChanged"), nullptr, FlowControlChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "parityChanged"), nullptr, ParityChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "requestToSendChanged"), nullptr, RequestToSendChanged);
					tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "stopBitsChanged"), nullptr, StopBitsChanged);
				}
				{
					v8::Local<v8::ObjectTemplate> direction = v8::ObjectTemplate::New(isolate);
					direction->Set(isolate, "Input", v8::Int32::New(isolate, QSerialPort::Direction::Input));
					direction->Set(isolate, "Output", v8::Int32::New(isolate, QSerialPort::Direction::Output));
					direction->Set(isolate, "AllDirections", v8::Int32::New(isolate, QSerialPort::Direction::AllDirections));
					tpl->Set(isolate, "Direction", direction);

					v8::Local<v8::ObjectTemplate> baudRate = v8::ObjectTemplate::New(isolate);
					baudRate->Set(isolate, "Baud1200", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud1200));
					baudRate->Set(isolate, "Baud2400", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud2400));
					baudRate->Set(isolate, "Baud4800", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud4800));
					baudRate->Set(isolate, "Baud9600", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud9600));
					baudRate->Set(isolate, "Baud19200", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud19200));
					baudRate->Set(isolate, "Baud38400", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud38400));
					baudRate->Set(isolate, "Baud57600", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud57600));
					baudRate->Set(isolate, "Baud115200", v8::Int32::New(isolate, QSerialPort::BaudRate::Baud115200));
					tpl->Set(isolate, "BaudRate", baudRate);

					v8::Local<v8::ObjectTemplate> dataBits = v8::ObjectTemplate::New(isolate);
					dataBits->Set(isolate, "Data5", v8::Int32::New(isolate, QSerialPort::DataBits::Data5));
					dataBits->Set(isolate, "Data6", v8::Int32::New(isolate, QSerialPort::DataBits::Data6));
					dataBits->Set(isolate, "Data7", v8::Int32::New(isolate, QSerialPort::DataBits::Data7));
					dataBits->Set(isolate, "Data8", v8::Int32::New(isolate, QSerialPort::DataBits::Data8));
					tpl->Set(isolate, "DataBits", dataBits);

					v8::Local<v8::ObjectTemplate> parity = v8::ObjectTemplate::New(isolate);
					parity->Set(isolate, "NoParity", v8::Int32::New(isolate, QSerialPort::Parity::NoParity));
					parity->Set(isolate, "EvenParity", v8::Int32::New(isolate, QSerialPort::Parity::EvenParity));
					parity->Set(isolate, "OddParity", v8::Int32::New(isolate, QSerialPort::Parity::OddParity));
					parity->Set(isolate, "SpaceParity", v8::Int32::New(isolate, QSerialPort::Parity::SpaceParity));
					parity->Set(isolate, "MarkParity", v8::Int32::New(isolate, QSerialPort::Parity::MarkParity));
					tpl->Set(isolate, "Parity", parity);

					v8::Local<v8::ObjectTemplate> stopBits = v8::ObjectTemplate::New(isolate);
					stopBits->Set(isolate, "OneStop", v8::Int32::New(isolate, QSerialPort::StopBits::OneStop));
					stopBits->Set(isolate, "OneAndHalfStop", v8::Int32::New(isolate, QSerialPort::StopBits::OneAndHalfStop));
					stopBits->Set(isolate, "TwoStop", v8::Int32::New(isolate, QSerialPort::StopBits::TwoStop));
					tpl->Set(isolate, "StopBits", stopBits);

					v8::Local<v8::ObjectTemplate> flowControl = v8::ObjectTemplate::New(isolate);
					flowControl->Set(isolate, "NoFlowControl", v8::Int32::New(isolate, QSerialPort::FlowControl::NoFlowControl));
					flowControl->Set(isolate, "HardwareControl", v8::Int32::New(isolate, QSerialPort::FlowControl::HardwareControl));
					flowControl->Set(isolate, "SoftwareControl", v8::Int32::New(isolate, QSerialPort::FlowControl::SoftwareControl));
					tpl->Set(isolate, "FlowControl", flowControl);

					v8::Local<v8::ObjectTemplate> pinoutSignal = v8::ObjectTemplate::New(isolate);
					pinoutSignal->Set(isolate, "NoSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::NoSignal));
					pinoutSignal->Set(isolate, "DataTerminalReadySignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::DataTerminalReadySignal));
					pinoutSignal->Set(isolate, "DataCarrierDetectSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::DataCarrierDetectSignal));
					pinoutSignal->Set(isolate, "DataSetReadySignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::DataSetReadySignal));
					pinoutSignal->Set(isolate, "RingIndicatorSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::RingIndicatorSignal));
					pinoutSignal->Set(isolate, "RequestToSendSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::RequestToSendSignal));
					pinoutSignal->Set(isolate, "ClearToSendSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::ClearToSendSignal));
					pinoutSignal->Set(isolate, "SecondaryTransmittedDataSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::SecondaryTransmittedDataSignal));
					pinoutSignal->Set(isolate, "SecondaryReceivedDataSignal", v8::Int32::New(isolate, QSerialPort::PinoutSignal::SecondaryReceivedDataSignal));
					tpl->Set(isolate, "PinoutSignal", pinoutSignal);

					v8::Local<v8::ObjectTemplate> serialPortError = v8::ObjectTemplate::New(isolate);
					serialPortError->Set(isolate, "NoError", v8::Int32::New(isolate, QSerialPort::SerialPortError::NoError));
					serialPortError->Set(isolate, "DeviceNotFoundError", v8::Int32::New(isolate, QSerialPort::SerialPortError::DeviceNotFoundError));
					serialPortError->Set(isolate, "PermissionError", v8::Int32::New(isolate, QSerialPort::SerialPortError::PermissionError));
					serialPortError->Set(isolate, "OpenError", v8::Int32::New(isolate, QSerialPort::SerialPortError::OpenError));
					serialPortError->Set(isolate, "WriteError", v8::Int32::New(isolate, QSerialPort::SerialPortError::WriteError));
					serialPortError->Set(isolate, "ReadError", v8::Int32::New(isolate, QSerialPort::SerialPortError::ReadError));
					serialPortError->Set(isolate, "ResourceError", v8::Int32::New(isolate, QSerialPort::SerialPortError::ResourceError));
					serialPortError->Set(isolate, "UnsupportedOperationError", v8::Int32::New(isolate, QSerialPort::SerialPortError::UnsupportedOperationError));
					serialPortError->Set(isolate, "UnknownError", v8::Int32::New(isolate, QSerialPort::SerialPortError::UnknownError));
					serialPortError->Set(isolate, "TimeoutError", v8::Int32::New(isolate, QSerialPort::SerialPortError::TimeoutError));
					serialPortError->Set(isolate, "NotOpenError", v8::Int32::New(isolate, QSerialPort::SerialPortError::NotOpenError));
					tpl->Set(isolate, "SerialPortError", serialPortError);
				}
			}

		protected:

			static void AtEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = p->d_func()->atEnd();
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesAvailable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::BigInt::New(isolate, p->d_func()->bytesAvailable());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesToWrite(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::BigInt::New(isolate, p->d_func()->bytesToWrite());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CanReadLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = p->d_func()->canReadLine();
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto directions = std::invoke([&]() {
							if (V8_IsNumber(args, 0)) {
								return static_cast<QSerialPort::Directions>(args[0]->Int32Value(context).FromJust());
							}
							else {
								return static_cast<QSerialPort::Directions>(QSerialPort::AllDirections);
							}
							});

						auto result = p->d_func()->clear(directions);
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ClearError(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						p->d_func()->clearError();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						p->d_func()->close();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Flush(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = p->d_func()->flush();
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Handle(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::External::New(isolate, p->d_func()->handle());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSequential(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = p->d_func()->isSequential();
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Open(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto mode = std::invoke([&]() {
							if (V8_IsNumber(args, 0)) {
								return static_cast<QIODevice::OpenMode>(args[0]->Int32Value(context).FromJust());
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[mode] error."));
							});

						auto result = p->d_func()->open(mode);
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PinoutSignals(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = p->d_func()->pinoutSignals();
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PortName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->portName()));
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadBufferSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::BigInt::New(isolate, p->d_func()->readBufferSize());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetPort(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (!p)
						return;

					p->d_func()->setPort(***SerialPortInfo::FromValue(isolate, args[0]));
				}

				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetPortName(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto name = std::invoke([&]() {
							return  convert::String::To(isolate, value);
							});

						p->d_func()->setPortName(name);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetReadBufferSize(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto size = std::invoke([&]() {
							if (V8_IsBigInt(args, 0)) {
								return args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[size] error."));
							});

						p->d_func()->setReadBufferSize(size);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForBytesWritten(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto msecs = std::invoke([&]() {
							if (V8_IsInt32(args, 0)) {
								return args[0]->Int32Value(context).FromJust();
							}
							else {
								return 30000;
							}
							});

						auto result = p->d_func()->waitForBytesWritten(msecs);
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForReadyRead(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto msecs = std::invoke([&]() {
							if (V8_IsInt32(args, 0)) {
								return args[0]->Int32Value(context).FromJust();
							}
							else {
								return 30000;
							}
							});

						auto result = p->d_func()->waitForReadyRead(msecs);
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BaudRate(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());
					if (p) {
						auto directions = std::invoke([&]() {
							if (V8_IsNumber(args, 0)) {
								return static_cast<QSerialPort::Directions>(args[0]->Int32Value(context).FromJust());
							}
							return static_cast<QSerialPort::Directions>(QSerialPort::AllDirections);
							});

						auto result = p->d_func()->baudRate(directions);
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetBaudRate(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(args.This());

					if (p) {
						auto baudRate = std::invoke([&]() {
							if (V8_IsNumber(args, 0)) {
								return args[0]->Int32Value(context).FromJust();
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[baudRate] error."));
							});
						auto directions = std::invoke([&]() {
							if (V8_IsNumber(args, 1)) {
								return static_cast<QSerialPort::Directions>(args[1]->Int32Value(context).FromJust());
							}
							return static_cast<QSerialPort::Directions>(QSerialPort::AllDirections);
							});
						p->d_func()->setBaudRate(baudRate, directions);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DataBits(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->dataBits();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDataBits(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto dataBits = std::invoke([&]() {
							if (value->IsNumber()) {
								return static_cast<QSerialPort::DataBits>(value->Int32Value(context).FromJust());
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[dataBits] error."));
							});
						p->d_func()->setDataBits(dataBits);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Parity(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->parity();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetParity(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto parity = std::invoke([&]() {
							if (value->IsNumber()) {
								return static_cast<QSerialPort::Parity>(value->Int32Value(context).FromJust());
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[parity] error."));
							});
						p->d_func()->setParity(parity);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StopBits(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->stopBits();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStopBits(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto stopBits = std::invoke([&]() {
							if (value->IsNumber()) {
								return static_cast<QSerialPort::StopBits>(value->Int32Value(context).FromJust());
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[stopBits] error."));
							});
						p->d_func()->setStopBits(stopBits);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FlowControl(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->flowControl();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetFlowControl(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto flowControl = std::invoke([&]() {
							if (value->IsNumber()) {
								return static_cast<QSerialPort::FlowControl>(value->Int32Value(context).FromJust());
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[flowControl] error."));
							});
						p->d_func()->setFlowControl(flowControl);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsDataTerminalReady(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->isDataTerminalReady();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetDataTerminalReady(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto dataTerminalReady = std::invoke([&]() {
							if (value->IsBoolean()) {
								return value->BooleanValue(isolate);
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[dataTerminalReady] error."));
							});

						p->d_func()->setDataTerminalReady(dataTerminalReady);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsRequestToSend(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->isRequestToSend();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetRequestToSend(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto requestToSend = std::invoke([&]() {
							if (value->IsBoolean()) {
								return value->BooleanValue(isolate);
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[requestToSend] error."));
							});

						p->d_func()->setRequestToSend(requestToSend);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsBreakEnabled(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->isBreakEnabled();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetBreakEnabled(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());

					if (p) {
						auto breakEnabled = std::invoke([&]() {
							if (value->IsBoolean()) {
								return value->BooleanValue(isolate);
							}
							isolate->ThrowException(V8_NEW_STRING_VAR(isolate, "#[breakEnabled] error."));
							});

						p->d_func()->setBreakEnabled(breakEnabled);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Error(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (p) {
						auto result = p->d_func()->error();
						info.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BaudRateChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::baudRateChanged, [weakPersistent](qint32 baudRate, QSerialPort::Directions directions) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, baudRate) , v8::Int32::New(isolate,directions) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::baudRateChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BreakEnabledChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::breakEnabledChanged, [weakPersistent](bool set) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Boolean::New(isolate, set) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::breakEnabledChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DataBitsChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::dataBitsChanged, [weakPersistent](QSerialPort::DataBits dataBits) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, dataBits) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::dataBitsChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void DataTerminalReadyChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::dataTerminalReadyChanged, [weakPersistent](bool set) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Boolean::New(isolate, set) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::dataTerminalReadyChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorOccurred(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::errorOccurred, [weakPersistent](QSerialPort::SerialPortError error) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, error) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::errorOccurred, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void FlowControlChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::flowControlChanged, [weakPersistent](QSerialPort::FlowControl flowControl) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, flowControl) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::flowControlChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ParityChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::parityChanged, [weakPersistent](QSerialPort::Parity parity) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, parity) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::parityChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RequestToSendChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::requestToSendChanged, [weakPersistent](bool set) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Boolean::New(isolate, set) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::requestToSendChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StopBitsChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QSerialPortWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QSerialPort::stopBitsChanged, [weakPersistent](QSerialPort::StopBits stopBits) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, stopBits) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_device) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QSerialPort::stopBitsChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
