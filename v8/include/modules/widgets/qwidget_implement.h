#pragma once
#include "framework.h"
#include <QWidget>
#include "qwidget_p.h"
#include "qwidget_wrapper.h"

namespace shelllet {
	namespace widgets {
		class Widget : public WidgetWrapper<QWidget, Widget, true>
		{
		public:
			using ReturnType = WidgetPrivate<QWidget, true>;
			using ReturnType2 = WidgetPrivate<QWidget, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			Widget(const v8::FunctionCallbackInfo<v8::Value>& args) :WidgetWrapper(*Private(args), args)
			{
			}
			Widget(QWidget* p, const v8::FunctionCallbackInfo<v8::Value>& args) : WidgetWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Widget(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : WidgetWrapper(isolate, tpl) {}
			Widget(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : WidgetWrapper(isolate, proto)
			{}

			static const char* Name() { return "Widget"; }
		public:
		};
	}
}
