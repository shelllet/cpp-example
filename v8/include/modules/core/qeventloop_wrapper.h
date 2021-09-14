#pragma once
#include "framework.h"
#include <QEventLoop>
#include "qobject_wrapper.h"

namespace shelllet {
	namespace core {
		template<typename T, bool> class QEventLoopPrivate;
		template<typename T, typename U, bool C>
		class QEventLoopWrapper : public QObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			QEventLoopWrapper(QEventLoopPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper(d, args) {
			}
			QEventLoopWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QEventLoopWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "isRunning", v8::FunctionTemplate::New(isolate, IsRunning));
				tpl->PrototypeTemplate()->Set(isolate, "processEvents", v8::FunctionTemplate::New(isolate, ProcessEvents));
				tpl->PrototypeTemplate()->Set(isolate, "exec", v8::FunctionTemplate::New(isolate, Exec));
				tpl->PrototypeTemplate()->Set(isolate, "exit", v8::FunctionTemplate::New(isolate, Exit));
				tpl->PrototypeTemplate()->Set(isolate, "quit", v8::FunctionTemplate::New(isolate, Quit));

				{
					v8::Local<v8::ObjectTemplate> process_events_flag = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, AllEvents);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, ExcludeUserInputEvents);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, ExcludeSocketNotifiers);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, WaitForMoreEvents);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, X11ExcludeTimers);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, EventLoopExec);
					V8_CREATE_ENUM_SYMBOL(process_events_flag, isolate, QEventLoop, ProcessEventsFlag, DialogExec);

					tpl->Set(isolate, "ProcessEventsFlag", process_events_flag);
				}
			}

		protected:

			static void Exec(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents;
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							flags = static_cast<QEventLoop::ProcessEventsFlags>(args[0]->Int32Value(context).FromJust());
						}
						v8::Unlocker unlocker(isolate);
						p->d_func()->exec(flags);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Exit(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					int return_code = 0;
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							return_code = args[0]->Int32Value(context).FromJust();
						}
						p->d_func()->exit(return_code);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsRunning(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					if (p)
					{
						args.GetReturnValue().Set(p->d_func()->isRunning());
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProcessEvents(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					QEventLoop::ProcessEventsFlags flags = QEventLoop::AllEvents;

					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							flags = static_cast<QEventLoop::ProcessEventsFlags>(args[0]->Int32Value(context).FromJust());
							//p->loop_->processEvents(flags);
						}
						else if (args.Length() > 2 && args[0]->IsNumber() && args[1]->IsNumber()) {
							QEventLoop::ProcessEventsFlags flags = static_cast<QEventLoop::ProcessEventsFlags>(args[0]->Int32Value(context).FromJust());
							int max_time = static_cast<QEventLoop::ProcessEventsFlags>(args[1]->Int32Value(context).FromJust());
							p->d_func()->processEvents(flags, max_time);
						}
						else {
							p->d_func()->processEvents(flags);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WakeUp(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->wakeUp();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Quit(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QEventLoopWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->quit();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}