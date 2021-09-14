#pragma once
namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QTimerWrapper : public QObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QTimerWrapper(QTimerPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QTimerWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QTimerWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "callOnTimeout", v8::FunctionTemplate::New(isolate, CallOnTimeout));
				proto->Set(isolate, "interval", v8::FunctionTemplate::New(isolate, Interval));
				proto->Set(isolate, "intervalAsDuration", v8::FunctionTemplate::New(isolate, IntervalAsDuration));
				proto->Set(isolate, "isActive", v8::FunctionTemplate::New(isolate, IsActive));
				proto->Set(isolate, "isSingleShot", v8::FunctionTemplate::New(isolate, IsSingleShot));
				proto->Set(isolate, "remainingTime", v8::FunctionTemplate::New(isolate, RemainingTime));
				proto->Set(isolate, "remainingTimeAsDuration", v8::FunctionTemplate::New(isolate, RemainingTimeAsDuration));
				proto->Set(isolate, "setInterval", v8::FunctionTemplate::New(isolate, SetInterval));
				proto->Set(isolate, "setSingleShot", v8::FunctionTemplate::New(isolate, SetSingleShot));
				proto->Set(isolate, "setTimerType", v8::FunctionTemplate::New(isolate, SetTimerType));
				proto->Set(isolate, "start", v8::FunctionTemplate::New(isolate, Start));
				proto->Set(isolate, "timerId", v8::FunctionTemplate::New(isolate, TimerId));
				proto->Set(isolate, "timerType", v8::FunctionTemplate::New(isolate, TimerType));
				proto->Set(isolate, "stop", v8::FunctionTemplate::New(isolate, Stop));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "timeout"), nullptr, Timeout);
			}

		protected:
			static void CallOnTimeout(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Interval(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IntervalAsDuration(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsActive(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSingleShot(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RemainingTime(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RemainingTimeAsDuration(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					(*self)->setInterval(args[0]->Uint32Value(context).FromJust());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetSingleShot(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetTimerType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Start(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (args.Length() > 0) {
						(*self)->start(args[0]->Uint32Value(context).FromJust());
					}
					else {
						(*self)->start();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void TimerId(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void TimerType(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Stop(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(args.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Timeout(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QTimerWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent = std::make_shared<v8::Global<v8::Function>>(isolate, v8::Local<v8::Function>::Cast(value));
						QObject::connect(*self, &QTimer::timeout, [isolate, weakPersistent]() {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &QTimer::timeout, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}