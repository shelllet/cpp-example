#pragma once
#include "framework.h"

namespace shelllet {
	namespace network {
		template<typename T, bool> class QHostAddressPrivate;
		template<typename T, typename U, bool C>
		class QHostAddressWrapper : public core::ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QHostAddressWrapper(QHostAddressPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args)
			{
			}

			QHostAddressWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QHostAddressWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto) {
				{
					tpl->PrototypeTemplate()->Set(isolate, "clear", v8::FunctionTemplate::New(isolate, Clear));
					tpl->PrototypeTemplate()->Set(isolate, "isBroadcast", v8::FunctionTemplate::New(isolate, IsBroadcast));
					tpl->PrototypeTemplate()->Set(isolate, "isEqual", v8::FunctionTemplate::New(isolate, IsEqual));
					tpl->PrototypeTemplate()->Set(isolate, "isGlobal", v8::FunctionTemplate::New(isolate, IsGlobal));
					tpl->PrototypeTemplate()->Set(isolate, "isInSubnet", v8::FunctionTemplate::New(isolate, IsInSubnet));
					tpl->PrototypeTemplate()->Set(isolate, "isLinkLocal", v8::FunctionTemplate::New(isolate, IsLinkLocal));
					tpl->PrototypeTemplate()->Set(isolate, "isLoopback", v8::FunctionTemplate::New(isolate, IsLoopback));
					tpl->PrototypeTemplate()->Set(isolate, "isMulticast", v8::FunctionTemplate::New(isolate, IsMulticast));
					tpl->PrototypeTemplate()->Set(isolate, "isNull", v8::FunctionTemplate::New(isolate, IsNull));
					tpl->PrototypeTemplate()->Set(isolate, "isSiteLocal", v8::FunctionTemplate::New(isolate, IsSiteLocal));
					tpl->PrototypeTemplate()->Set(isolate, "isUniqueLocalUnicast", v8::FunctionTemplate::New(isolate, IsUniqueLocalUnicast));
					tpl->PrototypeTemplate()->Set(isolate, "setAddress", v8::FunctionTemplate::New(isolate, SetAddress));
					tpl->PrototypeTemplate()->Set(isolate, "swap", v8::FunctionTemplate::New(isolate, Swap));
					tpl->PrototypeTemplate()->Set(isolate, "toIPv4Address", v8::FunctionTemplate::New(isolate, ToIPv4Address));
					tpl->PrototypeTemplate()->SetAccessor(convert::String::New(isolate, "scopeId"), ScopeId, SetScopeId);
				}
				{
					v8::Local<v8::ObjectTemplate> special_address = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, Null);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, Broadcast);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, LocalHost);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, LocalHostIPv6);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, Any);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, AnyIPv6);
					V8_CREATE_ENUM_SYMBOL(special_address, isolate, QHostAddress, SpecialAddress, AnyIPv4);

					tpl->Set(isolate, "SpecialAddress", special_address);

					v8::Local<v8::ObjectTemplate> conversion_mode_flag = v8::ObjectTemplate::New(isolate);

					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, ConvertV4MappedToIPv4);
					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, ConvertV4CompatToIPv4);
					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, ConvertUnspecifiedAddress);
					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, ConvertLocalHost);
					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, TolerantConversion);
					V8_CREATE_ENUM_SYMBOL(conversion_mode_flag, isolate, QHostAddress, ConversionModeFlag, StrictConversion);

					tpl->Set(isolate, "ConversionModeFlag", conversion_mode_flag);
				}
			}

		private:

			static void Swap(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (!p)
					{
						return;
					}
					auto* address = HostAddress::FromValue(isolate, args[0]);
					if (address) {
						p->d_func()->swap(***address);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetAddress(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsString()) {
							v8::String::Utf8Value value(isolate, args[0]);

							p->d_func()->setAddress(QString::fromLocal8Bit(*value));
						}
						if (args.Length() > 0 && args[0]->IsNumber()) {
							QHostAddress::SpecialAddress address = static_cast<QHostAddress::SpecialAddress>(args[0]->Int32Value(context).FromJust());

							p->d_func()->setAddress(address);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ToIPv4Address(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->toIPv4Address();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ScopeId(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(info.This());
					if (p) {
						info.GetReturnValue().Set(convert::String::New(isolate, qPrintable(p->d_func()->scopeId())));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetScopeId(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(info.This());
					if (p) {
						v8::String::Utf8Value id(isolate, value);

						p->d_func()->setScopeId(QString::fromLocal8Bit(*id));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsEqual(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() > 0 && args[0]->IsObject()) {
							auto address = HostAddress::FromValue(isolate, args[0]);

							QHostAddress::ConversionMode mode = QHostAddress::TolerantConversion;
							if (args.Length() > 1 && args[1]->IsNumber()) {
								mode = static_cast<QHostAddress::ConversionMode>(args[1]->Int32Value(context).FromJust());
							}

							p->d_func()->isEqual(***address, mode);
						}
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsNull(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isNull();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Clear(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						p->d_func()->clear();
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsInSubnet(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						if (args.Length() < 2 || !args[0]->IsObject() || !args[1]->IsNumber()) {
							return;
						}

						auto address = HostAddress::FromValue(isolate, args[0]);

						int netmask = args[1]->Int32Value(context).FromJust();

						p->d_func()->isInSubnet(***address, netmask);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsLoopback(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isLoopback();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsGlobal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isGlobal();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsLinkLocal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isLinkLocal();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsSiteLocal(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isSiteLocal();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsUniqueLocalUnicast(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isUniqueLocalUnicast();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsMulticast(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isMulticast();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsBroadcast(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = convert::Object::UnWrap<QHostAddressWrapper<T, U, C>>(args.This());
					if (p)
					{
						auto result = p->d_func()->isBroadcast();

						args.GetReturnValue().Set(result);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}
