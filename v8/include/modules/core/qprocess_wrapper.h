#pragma once
#include "qiodevice_wrapper.h"
namespace shelllet {
	namespace core {
		template<typename T, bool> class QProcessPrivate;
		template<typename T, typename U, bool C>
		class QProcessWrapper : public QIODeviceWrapper<T, U, C>
		{
		public:

			template<bool M>
			QProcessWrapper(QProcessPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QIODeviceWrapper(d, args) {
			}
			QProcessWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QIODeviceWrapper(isolate, tpl) {}
			QProcessWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QIODeviceWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "arguments", v8::FunctionTemplate::New(isolate, Arguments));
				tpl->PrototypeTemplate()->Set(isolate, "closeWriteChannel", v8::FunctionTemplate::New(isolate, CloseWriteChannel));
				tpl->PrototypeTemplate()->Set(isolate, "createProcessArgumentsModifier", v8::FunctionTemplate::New(isolate, CreateProcessArgumentsModifier));
				tpl->PrototypeTemplate()->Set(isolate, "environment", v8::FunctionTemplate::New(isolate, Environment));
				tpl->PrototypeTemplate()->Set(isolate, "error", v8::FunctionTemplate::New(isolate, Error));
				tpl->PrototypeTemplate()->Set(isolate, "exitCode", v8::FunctionTemplate::New(isolate, ExitCode));
				tpl->PrototypeTemplate()->Set(isolate, "exitStatus", v8::FunctionTemplate::New(isolate, ExitStatus));
				tpl->PrototypeTemplate()->Set(isolate, "inputChannelMode", v8::FunctionTemplate::New(isolate, InputChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "kill", v8::FunctionTemplate::New(isolate, Kill));
				tpl->PrototypeTemplate()->Set(isolate, "nativeArguments", v8::FunctionTemplate::New(isolate, NativeArguments));
				tpl->PrototypeTemplate()->Set(isolate, "pid", v8::FunctionTemplate::New(isolate, Pid));
				tpl->PrototypeTemplate()->Set(isolate, "processChannelMode", v8::FunctionTemplate::New(isolate, ProcessChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "processEnvironment", v8::FunctionTemplate::New(isolate, ProcessEnvironment));
				tpl->PrototypeTemplate()->Set(isolate, "processId", v8::FunctionTemplate::New(isolate, ProcessId));
				tpl->PrototypeTemplate()->Set(isolate, "program", v8::FunctionTemplate::New(isolate, Program));
				tpl->PrototypeTemplate()->Set(isolate, "readAllStandardError", v8::FunctionTemplate::New(isolate, ReadAllStandardError));
				tpl->PrototypeTemplate()->Set(isolate, "readAllStandardOutput", v8::FunctionTemplate::New(isolate, ReadAllStandardOutput));
				tpl->PrototypeTemplate()->Set(isolate, "readChannel", v8::FunctionTemplate::New(isolate, ReadChannel));
				tpl->PrototypeTemplate()->Set(isolate, "readChannelMode", v8::FunctionTemplate::New(isolate, ReadChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "setArguments", v8::FunctionTemplate::New(isolate, SetArguments));
				tpl->PrototypeTemplate()->Set(isolate, "setCreateProcessArgumentsModifier", v8::FunctionTemplate::New(isolate, SetCreateProcessArgumentsModifier));
				tpl->PrototypeTemplate()->Set(isolate, "setEnvironment", v8::FunctionTemplate::New(isolate, SetEnvironment));
				tpl->PrototypeTemplate()->Set(isolate, "setInputChannelMode", v8::FunctionTemplate::New(isolate, SetInputChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "setNativeArguments", v8::FunctionTemplate::New(isolate, SetNativeArguments));
				tpl->PrototypeTemplate()->Set(isolate, "setProcessChannelMode", v8::FunctionTemplate::New(isolate, SetProcessChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "setProcessEnvironment", v8::FunctionTemplate::New(isolate, SetProcessEnvironment));
				tpl->PrototypeTemplate()->Set(isolate, "setProgram", v8::FunctionTemplate::New(isolate, SetProgram));
				tpl->PrototypeTemplate()->Set(isolate, "setReadChannel", v8::FunctionTemplate::New(isolate, SetReadChannel));
				tpl->PrototypeTemplate()->Set(isolate, "setReadChannelMode", v8::FunctionTemplate::New(isolate, SetReadChannelMode));
				tpl->PrototypeTemplate()->Set(isolate, "setStandardErrorFile", v8::FunctionTemplate::New(isolate, SetStandardErrorFile));
				tpl->PrototypeTemplate()->Set(isolate, "setStandardInputFile", v8::FunctionTemplate::New(isolate, SetStandardInputFile));
				tpl->PrototypeTemplate()->Set(isolate, "setStandardOutputFile", v8::FunctionTemplate::New(isolate, SetStandardOutputFile));
				tpl->PrototypeTemplate()->Set(isolate, "setStandardOutputProcess", v8::FunctionTemplate::New(isolate, SetStandardOutputProcess));
				tpl->PrototypeTemplate()->Set(isolate, "setWorkingDirectory", v8::FunctionTemplate::New(isolate, SetWorkingDirectory));
				tpl->PrototypeTemplate()->Set(isolate, "start", v8::FunctionTemplate::New(isolate, Start));
				tpl->PrototypeTemplate()->Set(isolate, "startDetached", v8::FunctionTemplate::New(isolate, StartDetached));
				tpl->PrototypeTemplate()->Set(isolate, "state", v8::FunctionTemplate::New(isolate, State));
				tpl->PrototypeTemplate()->Set(isolate, "terminate", v8::FunctionTemplate::New(isolate, Terminate));
				tpl->PrototypeTemplate()->Set(isolate, "waitForFinished", v8::FunctionTemplate::New(isolate, WaitForFinished));
				tpl->PrototypeTemplate()->Set(isolate, "waitForStarted", v8::FunctionTemplate::New(isolate, WaitForStarted));
				tpl->PrototypeTemplate()->Set(isolate, "workingDirectory", v8::FunctionTemplate::New(isolate, WorkingDirectory));

				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "errorOccurred"), nullptr, ErrorOccurred);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "finished"), nullptr, Finished);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "started"), nullptr, Started);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "readyReadStandardError"), nullptr, ReadyReadStandardError);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "readyReadStandardOutput"), nullptr, ReadyReadStandardOutput);
				tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "stateChanged"), nullptr, StateChanged);
				{
					v8::Local<v8::ObjectTemplate> processError = v8::ObjectTemplate::New(isolate);
					processError->Set(isolate, "FailedToStart", v8::Int32::New(isolate, QProcess::ProcessError::FailedToStart));
					processError->Set(isolate, "Crashed", v8::Int32::New(isolate, QProcess::ProcessError::Crashed));
					processError->Set(isolate, "Timedout", v8::Int32::New(isolate, QProcess::ProcessError::Timedout));
					processError->Set(isolate, "ReadError", v8::Int32::New(isolate, QProcess::ProcessError::ReadError));
					processError->Set(isolate, "WriteError", v8::Int32::New(isolate, QProcess::ProcessError::WriteError));
					processError->Set(isolate, "UnknownError", v8::Int32::New(isolate, QProcess::ProcessError::UnknownError));
					tpl->Set(isolate, "ProcessError", processError);

					v8::Local<v8::ObjectTemplate> processState = v8::ObjectTemplate::New(isolate);
					processState->Set(isolate, "NotRunning", v8::Int32::New(isolate, QProcess::ProcessState::NotRunning));
					processState->Set(isolate, "Starting", v8::Int32::New(isolate, QProcess::ProcessState::Starting));
					processState->Set(isolate, "Running", v8::Int32::New(isolate, QProcess::ProcessState::Running));
					tpl->Set(isolate, "ProcessState", processState);

					v8::Local<v8::ObjectTemplate> processChannel = v8::ObjectTemplate::New(isolate);
					processChannel->Set(isolate, "StandardOutput", v8::Int32::New(isolate, QProcess::ProcessChannel::StandardOutput));
					processChannel->Set(isolate, "StandardError", v8::Int32::New(isolate, QProcess::ProcessChannel::StandardError));
					tpl->Set(isolate, "ProcessChannel", processChannel);

					v8::Local<v8::ObjectTemplate> processChannelMode = v8::ObjectTemplate::New(isolate);
					processChannelMode->Set(isolate, "SeparateChannels", v8::Int32::New(isolate, QProcess::ProcessChannelMode::SeparateChannels));
					processChannelMode->Set(isolate, "MergedChannels", v8::Int32::New(isolate, QProcess::ProcessChannelMode::MergedChannels));
					processChannelMode->Set(isolate, "ForwardedChannels", v8::Int32::New(isolate, QProcess::ProcessChannelMode::ForwardedChannels));
					processChannelMode->Set(isolate, "ForwardedOutputChannel", v8::Int32::New(isolate, QProcess::ProcessChannelMode::ForwardedOutputChannel));
					processChannelMode->Set(isolate, "ForwardedErrorChannel", v8::Int32::New(isolate, QProcess::ProcessChannelMode::ForwardedErrorChannel));
					tpl->Set(isolate, "ProcessChannelMode", processChannelMode);

					v8::Local<v8::ObjectTemplate> inputChannelMode = v8::ObjectTemplate::New(isolate);
					inputChannelMode->Set(isolate, "ManagedInputChannel", v8::Int32::New(isolate, QProcess::InputChannelMode::ManagedInputChannel));
					inputChannelMode->Set(isolate, "ForwardedInputChannel", v8::Int32::New(isolate, QProcess::InputChannelMode::ForwardedInputChannel));
					tpl->Set(isolate, "InputChannelMode", inputChannelMode);

					v8::Local<v8::ObjectTemplate> exitStatus = v8::ObjectTemplate::New(isolate);
					exitStatus->Set(isolate, "NormalExit", v8::Int32::New(isolate, QProcess::ExitStatus::NormalExit));
					exitStatus->Set(isolate, "CrashExit", v8::Int32::New(isolate, QProcess::ExitStatus::CrashExit));
					tpl->Set(isolate, "ExitStatus", exitStatus);

					tpl->Set(isolate, "execute", v8::FunctionTemplate::New(isolate, Execute));
					tpl->Set(isolate, "nullDevice", v8::FunctionTemplate::New(isolate, NullDevice));
					tpl->Set(isolate, "startDetached", v8::FunctionTemplate::New(isolate, StartDetached));
					tpl->Set(isolate, "systemEnvironment", v8::FunctionTemplate::New(isolate, SystemEnvironment));
				}
			}

		protected:
			void setupChildProcess()
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					call(isolate, context, "setupChildProcess", 0, {});
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

		protected:

			static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::Array::New(isolate, context, p->d_func()->invoke<&QProcess::arguments>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CloseReadChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto channel = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return static_cast<QProcess::ProcessChannel>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QProcess::closeReadChannel>(channel);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CloseWriteChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QProcess::closeWriteChannel>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CreateProcessArgumentsModifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					// TODO:
					/*auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::createProcessArgumentsModifier>());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Environment(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::Array::New(isolate, context, p->d_func()->invoke<&QProcess::environment>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Error(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<qOverload<>(&QProcess::error)>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ExitCode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::exitCode>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ExitStatus(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::exitStatus>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void InputChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::inputChannelMode>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSequential(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QProcess::isSequential>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Kill(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QProcess::kill>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void NativeArguments(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::String::New(isolate, p->d_func()->invoke<&QProcess::nativeArguments>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Pid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					// TODO:
					//auto result = v8::BigInt::New(isolate, p->d_func()->invoke<&QProcess::pid>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProcessChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::processChannelMode>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProcessEnvironment(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					// TODO:
					//auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::processEnvironment>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ProcessId(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::BigInt::New(isolate, p->d_func()->invoke<&QProcess::processId>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Program(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::String::New(isolate, p->d_func()->invoke<&QProcess::program>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadAllStandardError(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::Uint8Array::New(isolate, context, p->d_func()->invoke<&QProcess::readAllStandardError>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadAllStandardOutput(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::Uint8Array::New(isolate, context, p->d_func()->invoke<&QProcess::readAllStandardOutput>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::readChannel>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::readChannelMode>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetArguments(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}

					if (!args[0]->IsArray())
						throw std::invalid_argument("!`Array` required at [0].");
					QStringList arguments;
					convert::Array::To(isolate, context, args[0], arguments);

					p->d_func()->invoke<&QProcess::setArguments>(arguments);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetCreateProcessArgumentsModifier(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto modifier = std::invoke([&]() {
						if (!args[0]->IsFunction())
							throw std::invalid_argument("!`Function` required at [0].");
						return v8::Local<v8::Function>::Cast(args[0]);
						});
#ifdef Q_OS_WIN

					p->d_func()->invoke<&QProcess::setCreateProcessArgumentsModifier>([](QProcess::CreateProcessArguments*) {
						});
#endif // Q_OS_WIN
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetEnvironment(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					if (!args[0]->IsArray())
						throw std::invalid_argument("!`Array` required at [0].");
					QStringList environment;
					convert::Array::To(isolate, context, args[0], environment);

					p->d_func()->invoke<&QProcess::setEnvironment>(environment);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetInputChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto mode = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<QProcess::InputChannelMode>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QProcess::setInputChannelMode>(mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetNativeArguments(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto arguments = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return convert::String::To(isolate, args[0]);
						});

					p->d_func()->invoke<&QProcess::setNativeArguments>(arguments);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetProcessChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto mode = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<QProcess::ProcessChannelMode>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QProcess::setProcessChannelMode>(mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetProcessEnvironment(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					// TODO:
				/*	auto environment = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					p->d_func()->invoke<&QProcess::setProcessEnvironment>(environment);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetProgram(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto program = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					p->d_func()->invoke<&QProcess::setProgram>(program);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetReadChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto channel = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<QProcess::ProcessChannel>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QProcess::setReadChannel>(channel);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetReadChannelMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto mode = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return static_cast<QProcess::ProcessChannelMode>(args[0]->Int32Value(context).FromJust());
						});

					p->d_func()->invoke<&QProcess::setReadChannelMode>(mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStandardErrorFile(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto fileName = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return convert::String::To(isolate, args[0]);
						});

					auto mode = std::invoke([&]() {
						if (args[1]->IsInt32())
							return static_cast<QIODevice::OpenMode>(args[1]->Int32Value(context).FromJust());
						return static_cast<QIODevice::OpenMode>(QIODevice::Truncate);
						});

					p->d_func()->invoke<&QProcess::setStandardErrorFile>(fileName, mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStandardInputFile(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto fileName = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return convert::String::To(isolate, args[0]);
						});

					p->d_func()->invoke<&QProcess::setStandardInputFile>(fileName);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStandardOutputFile(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto fileName = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					auto mode = std::invoke([&]() {
						if (args[1]->IsInt32())
							return static_cast<QIODevice::OpenMode>(args[1]->Int32Value(context).FromJust());
						return static_cast<QIODevice::OpenMode>(QIODevice::Truncate);
						});

					p->d_func()->invoke<&QProcess::setStandardOutputFile>(fileName, mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetStandardOutputProcess(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto* destination = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return convert::Object::UnWrap<QProcess>(args[0]->ToObject(context).ToLocalChecked());
						});

					p->d_func()->invoke<&QProcess::setStandardOutputProcess>(destination);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto dir = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					p->d_func()->invoke<&QProcess::setWorkingDirectory>(dir);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Start(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto program = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					QStringList arguments;
					convert::Array::To(isolate, context, args[1], arguments);

					auto mode = std::invoke([&]() {
						if (args[2]->IsInt32())
							return static_cast<QIODevice::OpenMode>(args[2]->Int32Value(context).FromJust());
						return static_cast<QIODevice::OpenMode>(QIODevice::ReadWrite);
						});

					if (program.isEmpty() && arguments.isEmpty()) {
						p->d_func()->invoke<qOverload<QIODevice::OpenMode>(&QProcess::start)>(mode);
					}
					else if (arguments.isEmpty()) {
						p->d_func()->invoke<qOverload<const QString&, QIODevice::OpenMode>(&QProcess::start)>(program, mode);
					}
					else {
						p->d_func()->invoke<qOverload<const QString&, const QStringList&, QIODevice::OpenMode>(&QProcess::start)>(program, arguments, mode);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void State(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QProcess::state>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Terminate(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					p->d_func()->invoke<&QProcess::terminate>();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForFinished(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto msecs = std::invoke([&]() {
						if (args[0]->IsInt32())
							return args[0]->Int32Value(context).FromJust();
						return 30000;
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QProcess::waitForFinished>(msecs));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForStarted(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto msecs = std::invoke([&]() {
						if (args[0]->IsInt32())
							return args[0]->Int32Value(context).FromJust();
						return 30000;
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QProcess::waitForStarted>(msecs));
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto result = convert::String::New(isolate, p->d_func()->invoke<&QProcess::workingDirectory>());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Execute(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto program = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return  convert::String::To(isolate, args[0]);
						});

					QStringList arguments;
					convert::Array::To(isolate, context, args[1], arguments);
					v8::Local<v8::Number>result;
					if (arguments.isEmpty()) {
						result = v8::Int32::New(isolate, QProcess::execute(program));
					}
					else {
						result = v8::Int32::New(isolate, QProcess::execute(program, arguments));
					}

					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void NullDevice(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto result = convert::String::New(isolate, QProcess::nullDevice());
					args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StartDetached(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					bool ok = false;
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(args.This());
					if (!p) {
						auto program = std::invoke([&]() {
							if (!args[0]->IsString())
								throw std::invalid_argument("!`String` required at [0].");
							return convert::String::To(isolate, args[0]);
							});

						QStringList arguments;
						convert::Array::To(isolate, context, args[1], arguments);

						auto workingDirectory = std::invoke([&]() {
							if (args[2]->IsString())
								return  convert::String::To(isolate, args[2]);
							return QString();
							});

						//auto* pid = std::invoke([&]() {
						//	if (args[3]->IsBigInt())
						//		return args[3]->ToBigInt(context).ToLocalChecked()->Int64Value();
						//	return nullptr;
						//	});

						if (arguments.isEmpty()) {
							ok = QProcess::startDetached(program);
						}
						else {
							ok = QProcess::startDetached(program, arguments, workingDirectory);
						}
					}
					else {
						ok = p->d_func()->invoke<qOverload<qint64*>(&QProcess::startDetached)>(nullptr);
					}
					args.GetReturnValue().Set(v8::Boolean::New(isolate, ok));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SystemEnvironment(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					args.GetReturnValue().Set(convert::Array::New(isolate, context, QProcess::systemEnvironment()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorOccurred(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QProcess::errorOccurred, [weakPersistent](QProcess::ProcessError error) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, error) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QProcess::errorOccurred, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void Started(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QProcess::started, [weakPersistent]() {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QProcess::started, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			static void Finished(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), qOverload<int, QProcess::ExitStatus>(&QProcess::finished), [weakPersistent](int exitCode, QProcess::ExitStatus exitStatus) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, exitCode), v8::Int32::New(isolate, exitStatus) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), qOverload<int, QProcess::ExitStatus>(&QProcess::finished), nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadyReadStandardError(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QProcess::readyReadStandardError, [weakPersistent]() {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QProcess::readyReadStandardError, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadyReadStandardOutput(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p) {
						return;
					}
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QProcess::readyReadStandardOutput, [weakPersistent]() {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QProcess::readyReadStandardOutput, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StateChanged(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QProcessWrapper<T, U, C>>(info.This());
					if (!p)
						return;
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent =
							std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
								});

						QObject::connect(p->d_func(), &QProcess::stateChanged, [weakPersistent](QProcess::ProcessState state) {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { v8::Int32::New(isolate, state) };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									qCCritical(shelllet_common) << tryCatch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QProcess::stateChanged, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
