#pragma once
#include "framework.h"
#include <qmodbusdataunit.h>
#include "qmodbusdataunit_p.h"
#include "qmodbusdataunit_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusDataUnit : public QModbusDataUnitWrapper<QModbusDataUnit, ModbusDataUnit, true>
		{
		public:
			using ReturnType = QModbusDataUnitPrivate<QModbusDataUnit, true>;
			using ReturnType2 = QModbusDataUnitPrivate<QModbusDataUnit, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				v8::Isolate* isolate = args.GetIsolate();
				if (args[0]->IsExternal()) {
					void* p = args[0].As<v8::External>()->Value();
					if (p)
						return new ReturnType(isolate, args.This(), *static_cast<QModbusDataUnit*>(p));
				}
				QModbusDataUnit::RegisterType type = static_cast<QModbusDataUnit::RegisterType>(args[0]->Int32Value(isolate->GetCurrentContext()).FromJust());
				if (args.Length() == 1) {
					return new ReturnType(isolate, args.This(), type);
				}
				else {
					int address = args[1]->Int32Value(isolate->GetCurrentContext()).FromJust();
					if (args[2]->IsInt32Array()) {
						std::vector<std::uint16_t> t = ToArray<std::uint16_t>(isolate, args[2]);
						return new ReturnType(isolate, args.This(), type, address, QVector<quint16>::fromStdVector(t));
					}
					else {
						int size = args[2]->Int32Value(isolate->GetCurrentContext()).FromJust();
						return new ReturnType(isolate, args.This(), type, address, size);
					}
				}

				return new ReturnType(isolate, args.This());
			}

			ModbusDataUnit(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusDataUnitWrapper(*Private(args), args)
			{
			}
			ModbusDataUnit(QModbusDataUnit* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusDataUnitWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusDataUnit(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusDataUnitWrapper(isolate, tpl) {}
			ModbusDataUnit(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusDataUnitWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusDataUnit"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
