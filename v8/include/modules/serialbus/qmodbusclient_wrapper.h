#pragma once
#include "qmodbusdevice_wrapper.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool> class QModbusClientPrivate;
		template<typename T, typename U, bool C>
		class QModbusClientWrapper : public QModbusDeviceWrapper<T, U, C>
		{
		public:
			template<bool M>
			QModbusClientWrapper(QModbusClientPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QModbusDeviceWrapper(d, args) {
			}
			QModbusClientWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusDeviceWrapper(isolate, tpl) {}
			QModbusClientWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusDeviceWrapper(isolate, proto)
			{
				proto->Set(isolate, "setTimeout", v8::FunctionTemplate::New(isolate, SetTimeout));
				proto->Set(isolate, "sendReadRequest", v8::FunctionTemplate::New(isolate, SendReadRequest));
				proto->Set(isolate, "sendWriteRequest", v8::FunctionTemplate::New(isolate, SendWriteRequest));
			}

		protected:
			static void SetTimeout(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusClientWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					int newTimeout = args[0]->Int32Value(context).FromJust();

					(*self)->setTimeout(newTimeout);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void SendReadRequest(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusClientWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto* read = ModbusDataUnit::From(args[0]);
					if (!read) {
						throw std::invalid_argument(K_CONST_ERROR_INVLAID_PARAM);
					}

					int serverAddress = args[1]->Int32Value(context).FromJust();
					auto* reply = (*self)->sendReadRequest(**read, serverAddress);
					if (reply)
						args.GetReturnValue().Set(ModbusReply::New2(isolate, reply));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void SendWriteRequest(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusClientWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					auto* write = ModbusDataUnit::From(args[0]);
					if (!write) {
						throw std::invalid_argument(K_CONST_ERROR_INVLAID_PARAM);
					}

					int serverAddress = args[1]->Int32Value(context).FromJust();
					auto* reply = (*self)->sendWriteRequest(**write, serverAddress);
					if (reply)
						args.GetReturnValue().Set(ModbusReply::New2(isolate, reply));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}