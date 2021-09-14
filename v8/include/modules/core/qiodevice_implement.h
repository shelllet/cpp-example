#pragma once
#include "framework.h"
#include <QIODevice>
#include "core_module.h"
#include "qiodevice_p.h"
#include "qiodevice_wrapper.h"

namespace shelllet {
	namespace core {
		class IODevice : public QIODeviceWrapper<QIODevice, IODevice, true>
		{
			using ReturnType = QIODevicePrivate<QIODevice, true>;
			using ReturnType2 = QIODevicePrivate<QIODevice, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			IODevice(const v8::FunctionCallbackInfo<v8::Value>& args) : QIODeviceWrapper(*Private(args), args) {}
			IODevice(QIODevice* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QIODeviceWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			IODevice(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QIODeviceWrapper(isolate, tpl) {}
			IODevice(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QIODeviceWrapper(isolate, proto) {
			}

			static const char* Name() { return "QIODevice"; }

		public:
		};
	}
}
