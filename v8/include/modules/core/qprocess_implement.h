#pragma once
#include <QProcess>
#include "core_module.h"
#include "qprocess_p.h"
#include "qprocess_wrapper.h"
namespace shelllet {
	namespace core {
		class Process : public QProcessWrapper<QProcess, Process, true>
		{
			using ReturnType = QProcessPrivate<QProcess, true>;
			using ReturnType2 = QProcessPrivate<QProcess, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:

			Process(const v8::FunctionCallbackInfo<v8::Value>& args) : QProcessWrapper(*Param(args), args)
			{
			}
			Process(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QProcessWrapper(isolate, tpl) {}
			Process(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QProcessWrapper(isolate, proto) {
			}

			static const char* Name() {
				return "QProcess";
			}
		public:
		};
	}
}
