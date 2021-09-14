#pragma once

namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QSizeFWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QSizeFWrapper(QSizeFPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QSizeFWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QSizeFWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->Set(isolate, "boundedTo", v8::FunctionTemplate::New(isolate, BoundedTo));
				proto->Set(isolate, "expandedTo", v8::FunctionTemplate::New(isolate, ExpandedTo));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "height"), GetHeight, SetHeight);
				proto->Set(isolate, "isEmpty", v8::FunctionTemplate::New(isolate, IsEmpty));
				proto->Set(isolate, "isNull", v8::FunctionTemplate::New(isolate, IsNull));
				proto->Set(isolate, "isValid", v8::FunctionTemplate::New(isolate, IsValid));
				proto->Set(isolate, "scale", v8::FunctionTemplate::New(isolate, Scale));
				proto->Set(isolate, "scaled", v8::FunctionTemplate::New(isolate, Scaled));
				proto->Set(isolate, "transpose", v8::FunctionTemplate::New(isolate, Transpose));
				proto->Set(isolate, "transposed", v8::FunctionTemplate::New(isolate, Transposed));
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "width"), GetWidth, SetWidth);
			}

		protected:
			static void GetWidth(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(info.This());
					if (!p)
						return;
					info.GetReturnValue().Set((*p)->width());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(info.This());
					if (!p)
						return;
					(*p)->setWidth(value->NumberValue(context).FromJust());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(info.This());
					if (!p)
						return;
					info.GetReturnValue().Set((*p)->height());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(info.This());
					if (!p)
						return;
					(*p)->setHeight(value->NumberValue(context).FromJust());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void BoundedTo(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto otherSize = Size::From(args[0]);
					auto size = (*p)->boundedTo(**otherSize);
					args.GetReturnValue().Set(Size::New(isolate, v8::Number::New(isolate, size.width()), v8::Number::New(isolate, size.height())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void ExpandedTo(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					auto otherSize = Size::From(args[0]);
					auto size = (*p)->expandedTo(**otherSize);
					args.GetReturnValue().Set(Size::New(isolate, v8::Number::New(isolate, size.width()), v8::Number::New(isolate, size.height())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsEmpty(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					args.GetReturnValue().Set((*p)->isEmpty());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsNull(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					args.GetReturnValue().Set((*p)->isNull());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void IsValid(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					args.GetReturnValue().Set((*p)->isValid());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Scale(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					int index = 0;
					auto s = Size::From(args[0]);
					if (!s) {
						throw std::invalid_argument("! require `Size` value.");
					}
					auto mode = static_cast<Qt::AspectRatioMode>(args[index]->Int32Value(context).FromJust());
					(*p)->scale(**s, mode);
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Scaled(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					int index = 0;
					auto* s = Size::From(args[0]);
					if (!s) {
						throw std::invalid_argument("! require `Size` value.");
					}
					auto mode = static_cast<Qt::AspectRatioMode>(args[index]->Int32Value(context).FromJust());
					auto size = (*p)->scaled((**s), mode);
					args.GetReturnValue().Set(Size::New(isolate, v8::Number::New(isolate, size.width()), v8::Number::New(isolate, size.height())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Transpose(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* p = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!p) {
						return;
					}
					(*p)->transpose();
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Transposed(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<QSizeFWrapper<T, U, C>>(args.This());
					if (!self) {
						return;
					}
					auto size = (*self)->transposed();
					args.GetReturnValue().Set(Size::New(isolate, v8::Number::New(isolate, size.width()), v8::Number::New(isolate, size.height())));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}