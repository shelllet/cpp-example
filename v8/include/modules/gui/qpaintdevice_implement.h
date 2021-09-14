#pragma once
#include "framework.h"
#include <qpaintdevice.h>
#include "gui_module.h"
#include "qpaintdevice_p.h"
#include "qpaintdevice_wrapper.h"

namespace shelllet {
	namespace gui {
		class PaintDevice : public QPaintDeviceWrapper<QPaintDevice, PaintDevice, true>
		{
			using ReturnType = QPaintDevicePrivate<QPaintDevice, true>;
			using ReturnType2 = QPaintDevicePrivate<QPaintDevice, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			PaintDevice(const v8::FunctionCallbackInfo<v8::Value>& args) : QPaintDeviceWrapper(*Private(args), args) {}
			PaintDevice(QPaintDevice* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QPaintDeviceWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			PaintDevice(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) :QPaintDeviceWrapper(isolate, tpl) {}
			PaintDevice(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) :QPaintDeviceWrapper(isolate, proto) {}

			static const char* Name() { return "PaintDevice"; }
		public:
		};
	}
}
