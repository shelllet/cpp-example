#pragma once
#include "framework.h"
#include <QSerialPortInfo>

namespace shelllet {
	namespace device {
		class SerialPortInfo;
		template<typename T, bool> class QSerialPortInfoPrivate;
		template<typename T, typename U, bool C>
		class QSerialPortInfoWrapper : public core::ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QSerialPortInfoWrapper(QSerialPortInfoPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QSerialPortInfoWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QSerialPortInfoWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "description", v8::FunctionTemplate::New(isolate, Description));
				tpl->PrototypeTemplate()->Set(isolate, "hasProductIdentifier", v8::FunctionTemplate::New(isolate, HasProductIdentifier));
				tpl->PrototypeTemplate()->Set(isolate, "hasVendorIdentifier", v8::FunctionTemplate::New(isolate, HasVendorIdentifier));
				tpl->PrototypeTemplate()->Set(isolate, "isNull", v8::FunctionTemplate::New(isolate, IsNull));
				tpl->PrototypeTemplate()->Set(isolate, "manufacturer", v8::FunctionTemplate::New(isolate, Manufacturer));
				tpl->PrototypeTemplate()->Set(isolate, "portName", v8::FunctionTemplate::New(isolate, PortName));
				tpl->PrototypeTemplate()->Set(isolate, "productIdentifier", v8::FunctionTemplate::New(isolate, ProductIdentifier));
				tpl->PrototypeTemplate()->Set(isolate, "serialNumber", v8::FunctionTemplate::New(isolate, SerialNumber));
				tpl->PrototypeTemplate()->Set(isolate, "swap", v8::FunctionTemplate::New(isolate, Swap));
				tpl->PrototypeTemplate()->Set(isolate, "systemLocation", v8::FunctionTemplate::New(isolate, SystemLocation));
				tpl->PrototypeTemplate()->Set(isolate, "vendorIdentifier", v8::FunctionTemplate::New(isolate, VendorIdentifier));
				{
					tpl->Set(isolate, "availablePorts", v8::FunctionTemplate::New(isolate, AvailablePorts));
					tpl->Set(isolate, "standardBaudRates", v8::FunctionTemplate::New(isolate, StandardBaudRates));
				}
			}

		protected:

			static void Description(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->description()));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasProductIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::Boolean::New(isolate, p->d_func()->hasProductIdentifier());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void HasVendorIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::Boolean::New(isolate, p->d_func()->hasVendorIdentifier());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsNull(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::Boolean::New(isolate, p->d_func()->isNull());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Manufacturer(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->manufacturer()));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PortName(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->portName()));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProductIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::Int32::New(isolate, p->d_func()->productIdentifier());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SerialNumber(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->serialNumber()));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Swap(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (!p)
						return;
					p->d_func()->swap(***SerialPortInfo::FromValue(isolate, args[0]));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SystemLocation(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_NEW_STRING_VAR(isolate, qPrintable(p->d_func()->systemLocation()));
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void VendorIdentifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = v8::Int32::New(isolate, p->d_func()->vendorIdentifier());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void AvailablePorts(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_From_ObjectArray(isolate, context, "SerialPortInfo", p->d_func()->availablePorts());
						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StandardBaudRates(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QSerialPortInfoWrapper<T, U, C>>(args.This());
					if (p) {
						auto result = V8_From_Int32Array(isolate, context, p->d_func()->standardBaudRates());

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
