#pragma once
#include "framework.h"
#include <qiodevice.h>
#include "qobject_wrapper.h"

namespace shelllet {
	namespace core {
		template<typename T, bool> class QIODevicePrivate;
		template<typename T, typename U, bool C>
		class  QIODeviceWrapper : public QObjectWrapper<T, U, C>
		{
		public:

			template<bool M>
			QIODeviceWrapper(QIODevicePrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QObjectWrapper<M>(d, args) {
			}

			QIODeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QObjectWrapper(isolate, tpl) {}
			QIODeviceWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QObjectWrapper(isolate, proto) {
				tpl->PrototypeTemplate()->Set(isolate, "atEnd", v8::FunctionTemplate::New(isolate, AtEnd));
				tpl->PrototypeTemplate()->Set(isolate, "bytesAvailable", v8::FunctionTemplate::New(isolate, BytesAvailable));
				tpl->PrototypeTemplate()->Set(isolate, "bytesToWrite", v8::FunctionTemplate::New(isolate, BytesToWrite));
				tpl->PrototypeTemplate()->Set(isolate, "canReadLine", v8::FunctionTemplate::New(isolate, CanReadLine));
				tpl->PrototypeTemplate()->Set(isolate, "close", v8::FunctionTemplate::New(isolate, Close));
				tpl->PrototypeTemplate()->Set(isolate, "commitTransaction", v8::FunctionTemplate::New(isolate, CommitTransaction));
				tpl->PrototypeTemplate()->Set(isolate, "currentReadChannel", v8::FunctionTemplate::New(isolate, CurrentReadChannel));
				tpl->PrototypeTemplate()->Set(isolate, "currentWriteChannel", v8::FunctionTemplate::New(isolate, CurrentWriteChannel));
				tpl->PrototypeTemplate()->Set(isolate, "errorString", v8::FunctionTemplate::New(isolate, ErrorString));
				tpl->PrototypeTemplate()->Set(isolate, "getChar", v8::FunctionTemplate::New(isolate, GetChar));
				tpl->PrototypeTemplate()->Set(isolate, "isOpen", v8::FunctionTemplate::New(isolate, IsOpen));
				tpl->PrototypeTemplate()->Set(isolate, "isReadable", v8::FunctionTemplate::New(isolate, IsReadable));
				tpl->PrototypeTemplate()->Set(isolate, "isSequential", v8::FunctionTemplate::New(isolate, IsSequential));
				tpl->PrototypeTemplate()->Set(isolate, "isTextModeEnabled", v8::FunctionTemplate::New(isolate, IsTextModeEnabled));
				tpl->PrototypeTemplate()->Set(isolate, "isTransactionStarted", v8::FunctionTemplate::New(isolate, IsTransactionStarted));
				tpl->PrototypeTemplate()->Set(isolate, "isWritable", v8::FunctionTemplate::New(isolate, IsWritable));
				tpl->PrototypeTemplate()->Set(isolate, "open", v8::FunctionTemplate::New(isolate, Open));
				tpl->PrototypeTemplate()->Set(isolate, "openMode", v8::FunctionTemplate::New(isolate, OpenMode));
				tpl->PrototypeTemplate()->Set(isolate, "peek", v8::FunctionTemplate::New(isolate, Peek));
				tpl->PrototypeTemplate()->Set(isolate, "putChar", v8::FunctionTemplate::New(isolate, PutChar));
				tpl->PrototypeTemplate()->Set(isolate, "read", v8::FunctionTemplate::New(isolate, Read));
				tpl->PrototypeTemplate()->Set(isolate, "readAll", v8::FunctionTemplate::New(isolate, ReadAll));
				tpl->PrototypeTemplate()->Set(isolate, "readChannelCount", v8::FunctionTemplate::New(isolate, ReadChannelCount));
				tpl->PrototypeTemplate()->Set(isolate, "readLine", v8::FunctionTemplate::New(isolate, ReadLine));
				tpl->PrototypeTemplate()->Set(isolate, "reset", v8::FunctionTemplate::New(isolate, Reset));
				tpl->PrototypeTemplate()->Set(isolate, "rollbackTransaction", v8::FunctionTemplate::New(isolate, RollbackTransaction));
				tpl->PrototypeTemplate()->Set(isolate, "seek", v8::FunctionTemplate::New(isolate, Seek));
				tpl->PrototypeTemplate()->Set(isolate, "setCurrentReadChannel", v8::FunctionTemplate::New(isolate, SetCurrentReadChannel));
				tpl->PrototypeTemplate()->Set(isolate, "setCurrentWriteChannel", v8::FunctionTemplate::New(isolate, SetCurrentWriteChannel));
				tpl->PrototypeTemplate()->Set(isolate, "setTextModeEnabled", v8::FunctionTemplate::New(isolate, SetTextModeEnabled));
				tpl->PrototypeTemplate()->Set(isolate, "size", v8::FunctionTemplate::New(isolate, Size));
				tpl->PrototypeTemplate()->Set(isolate, "skip", v8::FunctionTemplate::New(isolate, Skip));
				tpl->PrototypeTemplate()->Set(isolate, "startTransaction", v8::FunctionTemplate::New(isolate, StartTransaction));
				tpl->PrototypeTemplate()->Set(isolate, "ungetChar", v8::FunctionTemplate::New(isolate, UngetChar));
				tpl->PrototypeTemplate()->Set(isolate, "waitForBytesWritten", v8::FunctionTemplate::New(isolate, WaitForBytesWritten));
				tpl->PrototypeTemplate()->Set(isolate, "waitForReadyRead", v8::FunctionTemplate::New(isolate, WaitForReadyRead));
				tpl->PrototypeTemplate()->Set(isolate, "write", v8::FunctionTemplate::New(isolate, Write));
				tpl->PrototypeTemplate()->Set(isolate, "writeChannelCount", v8::FunctionTemplate::New(isolate, WriteChannelCount));

				tpl->PrototypeTemplate()->SetAccessor(V8_NEW_STRING_VAR(isolate, "readyRead"), nullptr, ReadyRead);
				{
					v8::Local<v8::ObjectTemplate> open_mode_flag = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, NotOpen);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, ReadOnly);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, WriteOnly);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, ReadWrite);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, Append);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, Truncate);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, Text);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, Unbuffered);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, NewOnly);
					V8_CREATE_ENUM_SYMBOL(open_mode_flag, isolate, QIODevice, OpenModeFlag, ExistingOnly);

					tpl->Set(isolate, "OpenMode", open_mode_flag);
				}
			}
		protected:
			qint64 size() const
			{
				v8::Isolate* isolate = v8::Isolate::GetCurrent();

				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)
				{
					v8::Local<v8::Object> o = d_func()->object_this.Get(isolate);
					v8::Local<v8::Object> proto = o->GetPrototype()->ToObject(context).ToLocalChecked();

					v8::Local<v8::Value> value = proto->Get(context, V8_NEW_STRING_VAR(isolate, "size")).ToLocalChecked();

					auto f = v8::Local<v8::Function>::Cast(value);

					auto res = f->CallAsFunction(context, o, 0, {}).ToLocalChecked();
					if (!res.IsEmpty()) {
						if (res->IsNumber())
						{
							return res->Int32Value(context).FromJust();
						}
						else if (res->IsBigInt()) {
							auto n = res->ToBigInt(context).ToLocalChecked();

							if (!n.IsEmpty()) {
								return n->Int64Value();
							}
						}
					}
				}

				V8_CREATE_LOCAL_CONTEXT_END
					return 0;
			}
		public:

			static void OpenMode(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->openMode();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetTextModeEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsBoolean()) {
							p->d_func()->setTextModeEnabled(args[0]->BooleanValue(isolate));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsTextModeEnabled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isTextModeEnabled();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsOpen(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isOpen();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsReadable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isReadable();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsWritable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isWritable();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSequential(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isSequential();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadChannelCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->readChannelCount();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WriteChannelCount(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->writeChannelCount();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CurrentReadChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->currentReadChannel();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetCurrentReadChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							p->d_func()->setCurrentReadChannel(args[0]->Int32Value(context).FromJust());
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CurrentWriteChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->currentWriteChannel();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetCurrentWriteChannel(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							p->d_func()->setCurrentWriteChannel(args[0]->Int32Value(context).FromJust());
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Open(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							QIODevice::OpenMode mode = static_cast<QIODevice::OpenMode>(args[0]->Int32Value(context).FromJust());
							args.GetReturnValue().Set(p->d_func()->open(mode));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Close(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->close();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Size(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->size();

						args.GetReturnValue().Set(v8::BigInt::New(isolate, result));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Seek(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							qint64 pos = args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
							bool result = p->d_func()->seek(pos);

							args.GetReturnValue().Set(result);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void AtEnd(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->atEnd();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Reset(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->reset();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesAvailable(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->bytesAvailable();

						args.GetReturnValue().Set(v8::BigInt::New(isolate, result));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BytesToWrite(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->bytesToWrite();

						args.GetReturnValue().Set(v8::BigInt::New(isolate, result));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Read(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							qint64 maxSize = args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
							QByteArray bytes = p->d_func()->read(maxSize);

							v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, bytes.data(), bytes.length());

							v8::Local<v8::Uint8Array> array = v8::Uint8Array::New(buffer, 0, buffer->ByteLength());

							args.GetReturnValue().Set(array);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadAll(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->readAll();

						v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, result.data(), result.length());

						v8::Local<v8::Uint8Array> array = v8::Uint8Array::New(buffer, 0, buffer->ByteLength());

						args.GetReturnValue().Set(array);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						qint64 maxSize = 0;
						if (args.Length() > 0 && args[0]->IsNumber()) {
							maxSize = args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
						}
						QByteArray bytes = p->d_func()->readLine(maxSize);

						v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, bytes.data(), bytes.length());

						v8::Local<v8::Uint8Array> array = v8::Uint8Array::New(buffer, 0, buffer->ByteLength());

						args.GetReturnValue().Set(array);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CanReadLine(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->canReadLine();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StartTransaction(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->startTransaction();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void CommitTransaction(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->commitTransaction();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void RollbackTransaction(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->rollbackTransaction();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsTransactionStarted(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isTransactionStarted();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Write(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());

					if (V8_IsString(args, 0)) {
						qint64 bytes = p->d_func()->write(convert::String::To(isolate, args[0]).toUtf8());
						args.GetReturnValue().Set(v8::BigInt::New(isolate, bytes));
					}
					else if (V8_IsUint8Array(args, 0)) {
						QByteArray data;
						convert::Uint8Array::To(args[0], data);
						qint64 bytes = p->d_func()->write(data);
						args.GetReturnValue().Set(v8::BigInt::New(isolate, bytes));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Peek(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							qint64 maxSize = args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
							QByteArray bytes = p->d_func()->peek(maxSize);

							v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, bytes.data(), bytes.length());

							v8::Local<v8::Uint8Array> array = v8::Uint8Array::New(buffer, 0, buffer->ByteLength());

							args.GetReturnValue().Set(array);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Skip(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							qint64 maxSize = args[0]->ToBigInt(context).ToLocalChecked()->Int64Value();
							args.GetReturnValue().Set(v8::BigInt::New(isolate, p->d_func()->skip(maxSize)));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForReadyRead(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							int msecs = args[0]->Int32Value(context).FromJust();
							args.GetReturnValue().Set(p->d_func()->waitForReadyRead(msecs));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void WaitForBytesWritten(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsNumber()) {
							int msecs = args[0]->Int32Value(context).FromJust();
							args.GetReturnValue().Set(p->d_func()->waitForBytesWritten(msecs));
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void UngetChar(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsString()) {
							v8::String::Utf8Value s(isolate, args[0]);
							if (*s) {
								p->d_func()->ungetChar((*s)[0]);
							}
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void PutChar(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsString()) {
							v8::String::Utf8Value s(isolate, args[0]);
							if (*s) {
								p->d_func()->putChar((*s)[0]);
							}
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetChar(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						char c;
						p->d_func()->getChar(&c);
						args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, &c, v8::NewStringType::kNormal, 1).ToLocalChecked());
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ErrorString(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->errorString();

						args.GetReturnValue().Set(convert::String::New(isolate, qPrintable(result)));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ReadyRead(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QIODeviceWrapper<T, U, C>>(info.This());
					if (value->IsFunction()) {
						v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(value);
						std::shared_ptr<v8::Global<v8::Function>>weak_persistent = std::shared_ptr<v8::Global<v8::Function>>(new v8::Global<v8::Function>(isolate, f), [](v8::Global<v8::Function>* p) {
							p->Reset();
							delete p;
							});

						QObject::connect(p->d_func(), &QIODevice::readyRead, [weak_persistent]() {
							v8::Isolate* isolate = v8::Isolate::GetCurrent();
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch try_catch(isolate);

								weak_persistent->Get(isolate)->CallAsFunction(context, context->Global(), 0, {});
								if (try_catch.HasCaught()) {
									qCCritical(shelllet_filesystem) << try_catch.Exception();
								}
							}
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(p->d_func(), &QIODevice::readyRead, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
