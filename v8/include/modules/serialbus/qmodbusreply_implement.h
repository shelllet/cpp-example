#pragma once
#include "framework.h"
#include <qmodbusreply.h>
#include "qmodbusreply_p.h"
#include "qmodbusreply_wrapper.h"

namespace shelllet {
	namespace serialbus {
		//template<bool M, typename = void>
		class ModbusReply : public QModbusReplyWrapper<QModbusReply, ModbusReply, true>
		{
			using ReturnType = QModbusReplyPrivate<QModbusReply, true>;
			using ReturnType2 = QModbusReplyPrivate<QModbusReply, false>;
		public:
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				QModbusReply::ReplyType type = static_cast<QModbusReply::ReplyType>(args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust());
				int serverAddress = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromJust();
				return new ReturnType(args.GetIsolate(), args.This(), type, serverAddress);
			}

			ModbusReply(const v8::FunctionCallbackInfo<v8::Value>& args) :QModbusReplyWrapper(*Private(args), args)
			{
			}

			ModbusReply(QModbusReply* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QModbusReplyWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			ModbusReply(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QModbusReplyWrapper(isolate, tpl) {}
			ModbusReply(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QModbusReplyWrapper(isolate, proto)
			{}

			static const char* Name() { return "ModbusReply"; }
		protected:
			virtual void toString(std::stringstream& ss) const {}
		};
	}
}
