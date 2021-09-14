#pragma once
namespace shelllet {
	namespace global {
		template<typename T, typename U, bool C>
		class MyGlobalWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			MyGlobalWrapper(MyGlobalPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper<T, U, C>(d, args) {
			}
			MyGlobalWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper<T, U, C>(isolate, tpl)
			{
			}
			MyGlobalWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper<T, U, C>(isolate, proto)
			{
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "__dirname"), Dirname);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "__version"), Version);

				proto->Set(isolate, "chdir", v8::FunctionTemplate::New(isolate, Chdir));
				proto->Set(isolate, "sleep", v8::FunctionTemplate::New(isolate, Sleep));
				proto->Set(isolate, "iequals", v8::FunctionTemplate::New(isolate, IEquals));
				proto->Set(isolate, "start", v8::FunctionTemplate::New(isolate, Start));
				proto->Set(isolate, "setTimeout", v8::FunctionTemplate::New(isolate, SetTimeout));
				proto->Set(isolate, "clearTimeout", v8::FunctionTemplate::New(isolate, ClearTimeout));
				proto->Set(isolate, "setInterval", v8::FunctionTemplate::New(isolate, SetInterval));
				proto->Set(isolate, "clearInterval", v8::FunctionTemplate::New(isolate, ClearInterval));
				proto->Set(isolate, "getLastError", v8::FunctionTemplate::New(isolate, GetLastError));
				proto->Set(isolate, "setLastError", v8::FunctionTemplate::New(isolate, SetLastError));
				proto->Set(isolate, "writeFile", v8::FunctionTemplate::New(isolate, WriteFile));
				proto->Set(isolate, "toUpperCase", v8::FunctionTemplate::New(isolate, ToUpperCase));
				proto->Set(isolate, "toNumber", v8::FunctionTemplate::New(isolate, ToNumber));
				proto->Set(isolate, "waitForDebugger", v8::FunctionTemplate::New(isolate, WaitForDebugger));
			}

		protected:
			static void Version(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					info.GetReturnValue().Set(V8_NEW_WSTRING_VAR(isolate, MyGlobal::Version().toStdWString().c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Dirname(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					info.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, MyGlobal::dirname().c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Chdir(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args) {
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, MyGlobal::Chdir(ToString({ isolate, args[0] })).c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IEquals(const v8::FunctionCallbackInfo<v8::Value>& args) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					v8::String::Utf8Value s1(isolate, args[0]);
					v8::String::Utf8Value s2(isolate, args[1]);

					args.GetReturnValue().Set(v8::Boolean::New(isolate, MyGlobal::IEquals(*s1, *s2)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Start(const v8::FunctionCallbackInfo<v8::Value>& args) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args) {
					std::string filename = ToString({ isolate, args[0] });
					std::vector<std::string> arguments = {};
					for (int i = 1; i < args.Length(); i++) {
						arguments.push_back(ToString({ isolate, args[i] }));
					}

					MyGlobal::Start(filename, arguments);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Sleep(const v8::FunctionCallbackInfo<v8::Value>& args) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					int64_t ms = args[0]->Uint32Value(context).FromJust();
					v8::Unlocker unlocker(isolate);
					MyGlobal::Sleep(ms);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetTimeout(const v8::FunctionCallbackInfo<v8::Value>& args) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					int32_t timeout = 0;
					timeout = args[1]->Uint32Value(context).FromMaybe(timeout);
					if (args[0].IsEmpty() || !args[0]->IsFunction()) {
						throw std::invalid_argument("# function required.");
					}

					resource::TimerPrivate* p = new resource::TimerPrivate(isolate, args[0].As<v8::Function>());
					p->setTimeout([isolate](resource::TimerPrivate* p) {
						V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
						{
							v8::Local<v8::Function> fn = p->fn.Get(isolate);
							if (!fn.IsEmpty() && fn->IsFunction())
								fn->CallAsFunction(context, context->Global(), 0, {});
						}
						V8_CREATE_LOCAL_CONTEXT_END
						}, timeout);

					V8_GL_VALUE(isolate)->push_back(std::unique_ptr<Resource, Resource::Deleter>(p));
					args.GetReturnValue().Set(v8::External::New(isolate, p));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void ClearTimeout(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (!args[0]->IsExternal())
					{
						return;
					}
					if (auto* timer = static_cast<resource::TimerPrivate*>(args[0].As<v8::External>()->Value()); timer)
					{
						timer->clearTimeout();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void SetInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					int32_t repeat = 0;
					repeat = args[1]->Uint32Value(context).FromMaybe(repeat);

					if (args[0].IsEmpty() || !args[0]->IsFunction()) {
						throw std::invalid_argument("# function required.");
					}
					resource::TimerPrivate* p = new resource::TimerPrivate(isolate, args[0].As<v8::Function>());
					p->setInterval([isolate](resource::TimerPrivate* p) {
						V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
						{
							v8::Local<v8::Function> fn = p->fn.Get(isolate);
							if (!fn.IsEmpty() && fn->IsFunction())
								fn->CallAsFunction(context, context->Global(), 0, {});
						}
						V8_CREATE_LOCAL_CONTEXT_END
						}, repeat);
					V8_GL_VALUE(isolate)->push_back(std::unique_ptr<Resource, Resource::Deleter>(p));
					args.GetReturnValue().Set(v8::External::New(isolate, p));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void ClearInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (!args[0]->IsExternal())
					{
						return;
					}
					if (auto* timer = static_cast<resource::TimerPrivate*>(args[0].As<v8::External>()->Value()); timer)
					{
						timer->clearTimeout();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetLastError(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, error::GetLastErrorMessage().c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void SetLastError(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (args[0]->IsNumber()) {
						error::SetLastErrorMessage(args[0]->Int32Value(context).FromJust());
					}
					else if (args[0]->IsString()) {
						error::SetLastErrorMessage(ToString({ isolate, args[0] }));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WriteFile(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					std::string filename = ToString({ isolate, args[0] });
					std::string content = ToString({ isolate, args[1] });
					std::ios_base::openmode mode = std::ios_base::trunc;

					if (args.Length() > 2) {
						mode = static_cast<std::ios_base::openmode>(args[2]->Int32Value(context).FromJust());
					}
					MyGlobal::WriteFile(filename, content, mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void ToUpperCase(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					std::string string = ToString({ isolate, args[0] });

					int index = -1;
					if (args.Length() > 1) {
						index = args[1]->Int32Value(context).FromJust();
					}
					std::string result = MyGlobal::ToUpperCase(string, index);
					args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, result.c_str()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void ToNumber(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto v = ToArray<std::uint16_t>(isolate, args[0]);
					int type = 0;
					if (args.Length() > 1) {
						type = args[1]->Int32Value(context).FromJust();
					}
					args.GetReturnValue().Set(v8::Number::New(isolate, MyGlobal::ToNumber(v, type)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void WaitForDebugger(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto v = ToArray<std::uint16_t>(isolate, args[0]);
					int type = 0;
					if (args.Length() > 1) {
						type = args[1]->Int32Value(context).FromJust();
					}
					args.GetReturnValue().Set(v8::Number::New(isolate, MyGlobal::ToNumber(v, type)));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
