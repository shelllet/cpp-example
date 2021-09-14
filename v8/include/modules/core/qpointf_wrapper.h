#pragma once

namespace shelllet {
	namespace core {
		template<typename T, typename U, bool C>
		class QPointFWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template <bool M>
			QPointFWrapper(QPointFPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QPointFWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl)
			{
			}
			QPointFWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "x"), GetX, SetX);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "y"), GetY, SetY);
			}

		protected:
			static void GetX(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QPointWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), (*self)->x()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetX(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QPointWrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					(*self)->setX(value->NumberValue(context).FromJust());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetY(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QPointWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(v8::Number::New(info.GetIsolate(), (*self)->y()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetY(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<QPointWrapper<T, U, C>>(info.This());
					(*self)->setY(value->NumberValue(context).ToChecked());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}