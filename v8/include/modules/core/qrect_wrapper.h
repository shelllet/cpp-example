#pragma once

namespace shelllet {
	namespace core {
		template<typename T, bool> class QRectPrivate;
		template<typename T, typename U, bool C>
		class QRectWrapper : public ObjectWrapper<T, U, C>
		{
		public:
			template<bool M>
			QRectWrapper(QRectPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: ObjectWrapper(d, args) {
			}
			QRectWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : ObjectWrapper(isolate, tpl) {}
			QRectWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : ObjectWrapper(isolate, proto)
			{
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "x"), GetX, SetX);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "y"), GetY, SetY);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "width"), GetWidth, SetWidth);
				proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "height"), GetHeight, SetHeight);
			}

		protected:
			static void GetX(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());

					info.GetReturnValue().Set(v8::Int32::New(info.GetIsolate(), (*p)->x()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetX(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					(*p)->setX(value->Int32Value(context).ToChecked());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetY(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(v8::Int32::New(isolate, (*p)->y()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetY(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					(*p)->setY(value->Int32Value(context).ToChecked());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetWidth(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(v8::Int32::New(isolate, (*p)->width()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetWidth(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					(*p)->setWidth(value->Int32Value(context).ToChecked());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void GetHeight(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					info.GetReturnValue().Set(v8::Int32::New(isolate, (*p)->height()));
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void SetHeight(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* p = UnWrap<QRectWrapper<T, U, C>>(info.This());
					(*p)->setHeight(value->Int32Value(context).ToChecked());
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
		};
	}
}