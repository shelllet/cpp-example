#pragma once
#include "framework.h"
#include <qfiledevice.h>
#include "qiodevice_wrapper.h"

namespace shelllet {
	namespace core {
		template <typename T, typename U, bool> class QFileDevicePrivate;
		template <typename T, typename U, bool C>
		class  QFileDeviceWrapper : public QIODeviceWrapper<T, U, C>
		{
			template <typename T, typename U, bool> friend class QFileDevicePrivate;
		public:
			template <bool M>
			QFileDeviceWrapper(QFileDevicePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QIODeviceWrapper(d, args) {
			}

			QFileDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QIODeviceWrapper(isolate, tpl) {}
			QFileDeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QIODeviceWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "fileName", v8::FunctionTemplate::New(isolate, FileName));
			}
		protected:
			QString fileName() const
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();

				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Object> o = d_func()->object_this.Get(isolate);
					v8::Local<v8::Object> proto = o->GetPrototype()->ToObject(context).ToLocalChecked();

					v8::Local<v8::Value> value = proto->Get(context, V8_NEW_STRING_VAR(isolate, "fileName")).ToLocalChecked();

					auto f = v8::Local<v8::Function>::Cast(value);
					auto res = f->CallAsFunction(context, d_func()->object_this.Get(isolate), 0, {}).ToLocalChecked();
					if (!res.IsEmpty() && res->IsString()) {
						v8::String::Utf8Value name(isolate, res);

						if (*name) {
							return *name;
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
					return QString();
			}

		protected:

			static void FileName(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QFileDeviceWrapper<T, U, C>>(args.This());
					if (p) {
						auto name = p->d_func()->fileName();

						args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, qPrintable(name)));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
