#pragma once
#include "framework.h"
#include <qfile.h>
#include "qfiledevice_wrapper.h"
namespace shelllet {
	namespace core {
		template<typename T, bool> class QFilePrivate;
		template<typename T, typename U, bool C>
		class QFileWrapper : public QFileDeviceWrapper<T, U, C>
		{
		public:

			template<bool M>
			QFileWrapper(QFilePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QFileDeviceWrapper(d, args) {
			}
			QFileWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QFileDeviceWrapper(isolate, tpl) {}
			QFileWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QFileDeviceWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "remove", v8::FunctionTemplate::New(isolate, Remove));
				tpl->PrototypeTemplate()->Set(isolate, "setFileName", v8::FunctionTemplate::New(isolate, SetFileName));
				tpl->PrototypeTemplate()->Set(isolate, "rename", v8::FunctionTemplate::New(isolate, Rename));

				{
					tpl->Set(isolate, "remove", v8::FunctionTemplate::New(isolate, Remove));
					tpl->Set(isolate, "rename", v8::FunctionTemplate::New(isolate, Rename));
					tpl->Set(isolate, "removeAll", v8::FunctionTemplate::New(isolate, RemoveAll));
				}
			}

		protected:

			static void SetFileName(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QFileWrapper<T, U, C>>(args.This());
					if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value name(isolate, args[0]);
						p->d_func()->setFileName(*name);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Remove(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() == 0) {
						v8::String::Utf8Value target(args.GetIsolate(), args[0]);
						auto* p = convert::Object::UnWrap<QFileWrapper<T, U, C>>(args.This());
						if (p)
							p->d_func()->remove();
					}
					else if (args.Length() > 1 && args[0]->IsString())
					{
						v8::String::Utf8Value target(args.GetIsolate(), args[1]);
						QFile::remove(*target);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RemoveAll(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value target(args.GetIsolate(), args[0]);
						std::filesystem::remove_all(*target);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Rename(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto b = args.This()->IsObject();

					if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value target(args.GetIsolate(), args[0]);
						auto* p = convert::Object::UnWrap<QFileWrapper<T, U, C>>(args.This());
						if (p)
							args.GetReturnValue().Set(p->d_func()->rename(*target));
					}
					else if (args.Length() > 1 && args[0]->IsString() && args[1]->IsString())
					{
						v8::String::Utf8Value src(args.GetIsolate(), args[0]);
						v8::String::Utf8Value target(args.GetIsolate(), args[1]);
						args.GetReturnValue().Set(QFile::rename(*src, *target));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
