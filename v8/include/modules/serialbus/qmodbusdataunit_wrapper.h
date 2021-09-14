#pragma once

namespace shelllet {
	namespace serialbus {
		template<typename T, bool> class QModbusDataUnitPrivate;
		template<typename T, typename U, bool C>
		class QModbusDataUnitWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QModbusDataUnitWrapper(QModbusDataUnitPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QModbusDataUnitWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {
				auto registerType = v8::FunctionTemplate::New(isolate);
				registerType->Set(isolate, "Invalid", v8::Int32::New(isolate, QModbusDataUnit::Invalid));
				registerType->Set(isolate, "DiscreteInputs", v8::Int32::New(isolate, QModbusDataUnit::DiscreteInputs));
				registerType->Set(isolate, "Coils", v8::Int32::New(isolate, QModbusDataUnit::Coils));
				registerType->Set(isolate, "InputRegisters", v8::Int32::New(isolate, QModbusDataUnit::InputRegisters));
				registerType->Set(isolate, "HoldingRegisters", v8::Int32::New(isolate, QModbusDataUnit::HoldingRegisters));
				tpl->Set(isolate, "RegisterType", registerType);
			}
			QModbusDataUnitWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "isValid", v8::FunctionTemplate::New(isolate, IsValid));
				proto->Set(isolate, "registerType", v8::FunctionTemplate::New(isolate, RegisterType));
				proto->Set(isolate, "startAddress", v8::FunctionTemplate::New(isolate, StartAddress));
				proto->Set(isolate, "valueCount", v8::FunctionTemplate::New(isolate, ValueCount));
				proto->Set(isolate, "values", v8::FunctionTemplate::New(isolate, Values));
				proto->Set(isolate, "setRegisterType", v8::FunctionTemplate::New(isolate, SetRegisterType));
				proto->Set(isolate, "setStartAddress", v8::FunctionTemplate::New(isolate, SetStartAddress));
				proto->Set(isolate, "setValue", v8::FunctionTemplate::New(isolate, SetValue));
				proto->Set(isolate, "setValueCount", v8::FunctionTemplate::New(isolate, SetValueCount));
				proto->Set(isolate, "setValues", v8::FunctionTemplate::New(isolate, SetValues));
				proto->Set(isolate, "value", v8::FunctionTemplate::New(isolate, Value));
			}

		protected:
			static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set((*self)->isValid());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RegisterType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set(v8::Int32::New(isolate, (*self)->registerType()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StartAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set(v8::Int32::New(isolate, (*self)->startAddress()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ValueCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					args.GetReturnValue().Set(v8::Uint32::New(isolate, (*self)->valueCount()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Values(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetRegisterType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					QModbusDataUnit::RegisterType type = static_cast<QModbusDataUnit::RegisterType>(args[0]->Int32Value(context).FromJust());
					(*self)->setRegisterType(type);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStartAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					int address = args[0]->Int32Value(context).FromJust();
					(*self)->setStartAddress(address);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetValue(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					int index = args[0]->Int32Value(context).FromJust();
					quint16 value = args[1]->Uint32Value(context).FromJust();
					(*self)->setValue(index, value);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetValueCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					uint newCount = args[0]->Uint32Value(context).FromJust();
					(*self)->setValueCount(newCount);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetValues(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Value(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QModbusDataUnitWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
					int index = args[0]->Int32Value(context).FromJust();
					args.GetReturnValue().Set(v8::Uint32::New(isolate, (*self)->value(index)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}