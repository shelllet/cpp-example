#pragma once
#include "framework.h"
#include <qstring.h>
#include "qstring_p.h"
#include "qstring_wrapper.h"

namespace shelllet {
	namespace core {
		class  String : public QStringWrapper<QString, String, false>
		{
			using ReturnType = QRectPrivate<QString, true>;
			using ReturnType2 = QRectPrivate<QString, false>;
			ReturnType* Private(const v8::FunctionCallbackInfo<v8::Value>& args) {
				return new ReturnType(args.GetIsolate(), args.This());
			}
		public:
			String(const v8::FunctionCallbackInfo<v8::Value>& args) : QStringWrapper(*Private(args), args) {}
			String(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QRectWrapper(isolate, tpl) {}
			String(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QRectWrapper(isolate, proto) {
				tpl->Set(isolate, "chop", v8::FunctionTemplate::New(isolate, Chop));
				tpl->Set(isolate, "chopped", v8::FunctionTemplate::New(isolate, Chopped));
				tpl->Set(isolate, "contains", v8::FunctionTemplate::New(isolate, Contains));
				tpl->Set(isolate, "endsWith", v8::FunctionTemplate::New(isolate, EndsWith));
				tpl->Set(isolate, "isLower", v8::FunctionTemplate::New(isolate, IsLower));
				tpl->Set(isolate, "isSimpleText", v8::FunctionTemplate::New(isolate, IsSimpleText));
				tpl->Set(isolate, "isUpper", v8::FunctionTemplate::New(isolate, IsUpper));
				tpl->Set(isolate, "left", v8::FunctionTemplate::New(isolate, Left));
				tpl->Set(isolate, "mid", v8::FunctionTemplate::New(isolate, Mid));
				tpl->Set(isolate, "repeated", v8::FunctionTemplate::New(isolate, Repeated));
				tpl->Set(isolate, "right", v8::FunctionTemplate::New(isolate, Right));
				tpl->Set(isolate, "section", v8::FunctionTemplate::New(isolate, Section));
				tpl->Set(isolate, "simplified", v8::FunctionTemplate::New(isolate, Simplified));
				tpl->Set(isolate, "simplified", v8::FunctionTemplate::New(isolate, Simplified));
				tpl->Set(isolate, "simplified", v8::FunctionTemplate::New(isolate, Simplified));
				tpl->Set(isolate, "split", v8::FunctionTemplate::New(isolate, Split));
				tpl->Set(isolate, "startsWith", v8::FunctionTemplate::New(isolate, StartsWith));
				tpl->Set(isolate, "toCaseFolded", v8::FunctionTemplate::New(isolate, ToCaseFolded));
				tpl->Set(isolate, "toHtmlEscaped", v8::FunctionTemplate::New(isolate, ToHtmlEscaped));
				tpl->Set(isolate, "toLower", v8::FunctionTemplate::New(isolate, ToLower));
				tpl->Set(isolate, "toUpper", v8::FunctionTemplate::New(isolate, ToUpper));
				tpl->Set(isolate, "trimmed", v8::FunctionTemplate::New(isolate, Trimmed));
				tpl->Set(isolate, "trimmed", v8::FunctionTemplate::New(isolate, Trimmed));
				tpl->Set(isolate, "truncate", v8::FunctionTemplate::New(isolate, Truncate));
			}

		public:
			static const char* Name() { return "String"; }
			static void Chop(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto n = std::invoke([&]() {
							if (!args[0]->IsInt32())
								throw std::invalid_argument("!`Int32` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						p->d_func()->invoke<&QString::chop>(n);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Chopped(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto n = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::chopped>(n));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Contains(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto s = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return String::To(isolate, args[0]);
						});

					auto cs = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return Qt::CaseSensitive;
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::contains>(s, cs));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void EndsWith(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto s = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return String::To(isolate, args[0]);
						});

					auto cs = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return Qt::CaseSensitive;
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::endsWith>(s, cs));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsLower(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::isLower>());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSimpleText(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::isSimpleText>());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsUpper(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::isUpper>());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Left(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto n = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::left>(n));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Mid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto position = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto n = std::invoke([&]() {
						if (args[1]->IsInt32())
							return args[1]->Int32Value(context).FromJust();
						return -1;
						});

					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::mid>(position, n));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Repeated(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto times = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::repeated>(times));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Right(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*	auto n = std::invoke([&]() {
							if (!args[0]->IsInt32())
								throw std::invalid_argument("!`Int32` required at [0].");
							return args[0]->Int32Value(context).FromJust();
							});

						auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::right>(n));
						args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Section(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto sep = std::invoke([&]() {
						if (!args[0]->IsObject())
							throw std::invalid_argument("!`Object` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					auto start = std::invoke([&]() {
						if (!args[1]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [1].");
						return args[1]->Int32Value(context).FromJust();
						});

					auto end = std::invoke([&]() {
						if (args[2]->IsInt32())
							return args[2]->Int32Value(context).FromJust();
						return -1;
						});

					auto flags = std::invoke([&]() {
						if (args[3]->IsObject())
							return args[3]->Int32Value(context).FromJust();
						return SectionDefault;
						});

					auto result = String::New(isolate, p->d_func()->invoke<&QString::section>(sep, start, end, flags));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Simplified(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::simplified>());
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Split(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto sep = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return String::To(isolate, args[0]);
						});

					auto behavior = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return KeepEmptyParts;
						});

					auto cs = std::invoke([&]() {
						if (args[2]->IsObject())
							return args[2]->Int32Value(context).FromJust();
						return Qt::CaseSensitive;
						});

					auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::split>(sep, behavior, cs));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void StartsWith(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					/*auto s = std::invoke([&]() {
						if (!args[0]->IsString())
							throw std::invalid_argument("!`String` required at [0].");
						return String::To(isolate, args[0]);
						});

					auto cs = std::invoke([&]() {
						if (args[1]->IsObject())
							return args[1]->Int32Value(context).FromJust();
						return Qt::CaseSensitive;
						});

					auto result = v8::Boolean::New(isolate, p->d_func()->invoke<&QString::startsWith>(s, cs));
					args.GetReturnValue().Set(result);*/
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToCaseFolded(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					//auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::toCaseFolded>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToHtmlEscaped(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					//auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::toHtmlEscaped>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToLower(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					//	auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::toLower>());
						//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToUpper(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					//auto result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::toUpper>());
					//args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Trimmed(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					///*auto*/ result = v8::Int32::New(isolate, p->d_func()->invoke<&QString::trimmed>());
				//	args.GetReturnValue().Set(result);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Truncate(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QStringWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto pos = std::invoke([&]() {
						if (!args[0]->IsInt32())
							throw std::invalid_argument("!`Int32` required at [0].");
						return args[0]->Int32Value(context).FromJust();
						});

					//	p->d_func()->invoke<&QString::truncate>(pos);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
