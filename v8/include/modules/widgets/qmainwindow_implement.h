#pragma once
#include "framework.h"
#include <QMainWindow>
#include "qmainwindow_p.h"
#include "qmainwindow_wrapper.h"

namespace shelllet {
	namespace widgets {
		class MainWindow : public MainWindowWrapper<QMainWindow, MainWindow, true>
		{
		public:
			using ReturnType = MainWindowPrivate<QMainWindow, true>;
			using ReturnType2 = MainWindowPrivate<QMainWindow, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			MainWindow(const v8::FunctionCallbackInfo<v8::Value>& args) :MainWindowWrapper(*Private(args), args)
			{
			}
			MainWindow(QMainWindow* p, const v8::FunctionCallbackInfo<v8::Value>& args) : MainWindowWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			MainWindow(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : MainWindowWrapper(isolate, tpl) {}
			MainWindow(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : MainWindowWrapper(isolate, proto)
			{}

			static const char* Name() { return "MainWindow"; }
		public:
		};
	}
}
