#pragma once
#include <QWindow>
#include <QScreen>
#include "gui_module.h"
#include "qwindow_p.h"
#include "qwindow_wrapper.h"
#include "qpoint_implement.h"
#include "qobject_implement.h"
namespace shelllet {
	namespace gui {
		class Window : public QWindowWrapper<QWindow, Window, true>
		{
			using ReturnType = QImagePrivate<QWindow, true>;
			using ReturnType2 = QImagePrivate<QWindow, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType;
			}
		public:
			Window(const v8::FunctionCallbackInfo<v8::Value>& args) : QWindowWrapper(*Private(args), args) {}
			Window(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) :QWindowWrapper(isolate, tpl) {}
			Window(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) :QWindowWrapper(isolate, proto) {}

			static const char* Name() { return "Window"; }

		public:
		};
	}
}
