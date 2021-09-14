#pragma once
#include "framework.h"
#include "qobject_p.h"
#include "qobject_wrapper.h"

namespace shelllet {
	namespace core {
		class Object : public virtual QObjectWrapper<QObject, Object, true>
		{
			using ReturnType = QObjectPrivate<QObject, true>;
			using ReturnType2 = QObjectPrivate<QObject, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			Object(const v8::FunctionCallbackInfo<v8::Value>& args) : QObjectWrapper(*Param(args), args)
			{
			}
			Object(QObject* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QObjectWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			Object(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			Object(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
			}

		public:
			static const char* Name() {
				return "QObject";
			}
		};
	}
}
