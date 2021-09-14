#pragma once
#include "framework.h"
#include <qsystemtrayicon.h>
#include "qsystemtrayicon_p.h"
#include "qsystemtrayicon_wrapper.h"

namespace shelllet {
	namespace widgets {
		class SystemTrayIcon : public QSystemTrayIconWrapper<QSystemTrayIcon, SystemTrayIcon, true>
		{
		public:
			using ReturnType = QSystemTrayIconPrivate<QSystemTrayIcon, true>;
			using ReturnType2 = QSystemTrayIconPrivate<QSystemTrayIcon, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
			SystemTrayIcon(const v8::FunctionCallbackInfo<v8::Value>& args) :QSystemTrayIconWrapper(*Private(args), args)
			{
			}
			SystemTrayIcon(QSystemTrayIcon* p, const v8::FunctionCallbackInfo<v8::Value>& args) : QSystemTrayIconWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			SystemTrayIcon(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QSystemTrayIconWrapper(isolate, tpl) {}
			SystemTrayIcon(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QSystemTrayIconWrapper(isolate, proto)
			{
				tpl->Set(isolate, "isSystemTrayAvailable", v8::FunctionTemplate::New(isolate, IsSystemTrayAvailable));
				tpl->Set(isolate, "supportsMessages", v8::FunctionTemplate::New(isolate, SupportsMessages));
			}

		protected:
			void toString(std::stringstream& ss) const {}
		protected:
			static const char* Name() { return "SystemTrayIcon"; }
			static void IsSystemTrayAvailable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(self->d_func()->isSystemTrayAvailable());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SupportsMessages(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					args.GetReturnValue().Set(self->d_func()->supportsMessages());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
