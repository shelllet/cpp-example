#pragma once
#include "framework.h"
#include <qmodbuspdu.h>
#include "qmodbuspdu_p.h"
#include "qmodbuspdu_wrapper.h"

namespace shelllet {
	namespace serialbus {
		class ModbusPdu : public QModbusPduWrapper<QModbusPdu, ModbusPdu, true>
		{
		public:
			using ReturnType = QModbusPduPrivate<QModbusPdu, true>;
			using ReturnType2 = QModbusPduPrivate<QModbusPdu, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			ModbusPdu(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusPduWrapper(*Private(args), args)
			{
			}
			ModbusPdu(QModbusPdu* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusPduWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusPdu(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusPduWrapper(isolate, tpl) {}
			ModbusPdu(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusPduWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusPdu"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
