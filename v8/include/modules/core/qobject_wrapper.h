#pragma once

namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QObjectWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QObjectWrapper(QObjectPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args)
			{
			}
			QObjectWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QObjectWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "objectName"), ObjectName, SetObjectName);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "objectNameChanged"), nullptr, SetObjectNameChanged);

				proto->Set(isolate, "timerEvent", v8::FunctionTemplate::New(isolate, TimerEvent));
				//proto->PrototypeTemplate()->Set(isolate, "connect", v8::FunctionTemplate::New(isolate, Connect));
				//proto->PrototypeTemplate()->Set(isolate, "disconnect", v8::FunctionTemplate::New(isolate, Disconnect));
				if constexpr (!std::is_same_v<std::decay_t<T>, QTimer>) {
					proto->Set(isolate, "startTimer", v8::FunctionTemplate::New(isolate, StartTimer));
					proto->Set(isolate, "killTimer", v8::FunctionTemplate::New(isolate, KillTimer));
				}
			}

			virtual ~QObjectWrapper() {}
		protected:

			virtual void timerEvent(QTimerEvent* event)
			{
				//v8::Isolate* isolate = v8::Isolate::GetCurrent();

				//V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO_2(isolate) {
				//	if (!d_ptr->global_timer_event.IsEmpty()) {
				//		v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, event->timerId()) };
				//		d_ptr->global_timer_event.Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
				//	}
				//}
			}

			/*static void Connect(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() == 2 && args[0]->IsString() && args[1]->IsFunction()) {
						auto* p =  convert::Object::UnWrap<QObjectWrapper<T, U, C>>(args.This());
						v8::String::Utf8Value name(isolate, args[0]);

						QMetaObject::Connection conn = p->connect(*name);
						if (conn) {
							(*p)->pushConnection(*name, conn, CopyablePersistent<v8::Function>(isolate, v8::Local<v8::Function>::Cast(args[1])));
						}
						args.GetReturnValue().Set(conn);
					}
				}
V8_CREATE_LOCAL_CONTEXT_END
}

			static void Disconnect(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() > 0 && args[0]->IsString()) {
						v8::String::Utf8Value name(isolate, args[0]);
						auto* p =  convert::Object::UnWrap<QObjectWrapper<T, U, C>>(args.This());
						args.GetReturnValue().Set(p->disconnect(*name));
					}
				}
			}*/

			static void ObjectName(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QObjectWrapper<T, U, C>>(info.This());
					if (p)
					{
						info.GetReturnValue().Set(V8_NEW_WSTRING_VAR(isolate, (*p)->objectName().toStdWString().c_str()));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetObjectNameChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					if (value->IsFunction()) {
						auto* p = UnWrap<QObjectWrapper<T, U, C>>(info.This());

						//if (!(*p)->weak_objectnamechanged) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						QSharedPointer<v8::Global<v8::Function>>weak_persistent = QSharedPointer<v8::Global<v8::Function>>::create(isolate, f);
						//(*p)->weak_objectnamechanged = weak_persistent;

						QObject::connect((*p), &QObject::objectNameChanged, [weak_persistent](const QString& objectName) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);
								v8::Local<v8::Value> argv[] = { V8_NEW_WSTRING_VAR(isolate, objectName.toStdWString().c_str()) };
								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (try_catch.HasCaught()) {
									//qCCritical(shelllet_common) << try_catch.Exception();
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
						//}
					}
					else {
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetObjectName(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QObjectWrapper<T, U, C>>(info.This());
					v8::String::Utf8Value name(isolate, value);
					if (*name) {
						(*p)->setObjectName(*name);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StartTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					int ms = 0;
					Qt::TimerType timerType = Qt::CoarseTimer;

					if (args.Length() > 0 && args[0]->IsNumber()) {
						ms = args[0]->Int32Value(context).FromJust();
					}
					if (args.Length() > 1 && args[1]->IsNumber()) {
						timerType = static_cast<Qt::TimerType>(args[1]->Int32Value(context).FromJust());
					}
					auto* p = UnWrap<QObjectWrapper<T, U, C>>(args.This());

					if (p) {
						int id = (*p)->startTimer(ms, timerType);
						args.GetReturnValue().Set(id);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void KillTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args.Length() > 0 && args[0]->IsNumber()) {
						int id = args[0]->Int32Value(context).FromJust();
						auto* p = UnWrap<QObjectWrapper<T, U, C>>(args.This());

						if (p) {
							(*p)->killTimer(id);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void TimerEvent(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
			}
		};
	}
}
