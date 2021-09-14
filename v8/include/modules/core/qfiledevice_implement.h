#pragma once
#include "framework.h"
#include <qfiledevice.h>
#include "qfiledevice_p.h"
#include "qfiledevice_wrapper.h"

namespace shelllet {
	namespace core {
		class FileDevice : public QFileDeviceWrapper<QFileDevice, FileDevice, true>
		{
			using ReturnType = QFileDevicePrivate<QFileDevice, true>;
			using ReturnType2 = QFileDevicePrivate<QFileDevice, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			FileDevice(const v8::FunctionCallbackInfo<v8::Value>& args) :QFileDeviceWrapper(*Private(args), args) {
			}
			FileDevice(QFileDevice* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QFileDeviceWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			FileDevice(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QFileDeviceWrapper(isolate, tpl) {}
			FileDevice(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QFileDeviceWrapper(isolate, proto) {
			}

		public:
			static const char* Name();
		};
	}
}
