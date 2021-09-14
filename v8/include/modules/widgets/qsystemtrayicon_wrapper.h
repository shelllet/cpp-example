#pragma once
#include "core/qobject_wrapper.h"
namespace shelllet {
	namespace widgets {
		template<typename T, bool> class QSystemTrayIconPrivate;
		template<typename T, typename U, bool C>
		class QSystemTrayIconWrapper : public QObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			QSystemTrayIconWrapper(QSystemTrayIconPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QSystemTrayIconWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QSystemTrayIconWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "contextMenu", v8::FunctionTemplate::New(isolate, ContextMenu));
				proto->Set(isolate, "geometry", v8::FunctionTemplate::New(isolate, Geometry));
				proto->Set(isolate, "icon", v8::FunctionTemplate::New(isolate, Icon));
				proto->Set(isolate, "isVisible", v8::FunctionTemplate::New(isolate, IsVisible));
				proto->Set(isolate, "setContextMenu", v8::FunctionTemplate::New(isolate, SetContextMenu));
				proto->Set(isolate, "setIcon", v8::FunctionTemplate::New(isolate, SetIcon));
				proto->Set(isolate, "setToolTip", v8::FunctionTemplate::New(isolate, SetToolTip));
				proto->Set(isolate, "toolTip", v8::FunctionTemplate::New(isolate, ToolTip));
				proto->Set(isolate, "hide", v8::FunctionTemplate::New(isolate, Hide));
				proto->Set(isolate, "setVisible", v8::FunctionTemplate::New(isolate, SetVisible));
				proto->Set(isolate, "show", v8::FunctionTemplate::New(isolate, Show));
				proto->Set(isolate, "showMessage", v8::FunctionTemplate::New(isolate, ShowMessage));
				proto->Set(isolate, "showMessage", v8::FunctionTemplate::New(isolate, ShowMessage));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "activated"), nullptr, Activated);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "messageClicked"), nullptr, MessageClicked);
			}

		protected:
			static void ContextMenu(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Geometry(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Icon(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsVisible(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetContextMenu(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetIcon(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetToolTip(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToolTip(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Hide(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetVisible(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Show(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ShowMessage(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Activated(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weak_persistent = std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
							});

						QObject::connect(self->d_func(), &QSystemTrayIcon::activated, [isolate, weak_persistent](QSystemTrayIcon::ActivationReason reason) {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = {  };
								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(self->d_func(), &QSystemTrayIcon::activated, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void MessageClicked(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QSystemTrayIconWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weak_persistent = std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
							});

						QObject::connect(self->d_func(), &QSystemTrayIcon::messageClicked, [isolate, weak_persistent]() {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = {  };
								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(self->d_func(), &QSystemTrayIcon::messageClicked, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}