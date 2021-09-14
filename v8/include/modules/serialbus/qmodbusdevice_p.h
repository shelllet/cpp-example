#pragma once
#include "core/qobject_p.h"
namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusDevicePrivate : public QObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusDevicePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}

		protected:
			//	template<typename = std::enable_if<std::bool_constant<C>::value>::type>
			bool open() {
				if (hasOwnProperty(strrchr(__FUNCTION__, ':') + 1)) {
					//v8::Isolate* isolate = v8::Isolate::GetCurrent();

					//V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)

						/*v8::Local<v8::Object> o = object.Get(isolate);
						v8::Local<v8::Object> proto = o->GetPrototype()->ToObject(context).ToLocalChecked();

						v8::Local<v8::Value> value = proto->Get(context, V8_NEW_STRING_VAR(isolate, __FUNCTION__)).ToLocalChecked();

						auto f = v8::Local<v8::Function>::Cast(value);

						v8::Local<v8::Value> res = f->CallAsFunction(context, o, 0, {}).ToLocalChecked();*/

					v8::Local<v8::Value> value = call(__FUNCTION__);

					return value->BooleanValue(v8::Isolate::GetCurrent());

					//V8_CREATE_LOCAL_CONTEXT_END_WITH_RETURN(false)
				}
				if constexpr (std::is_abstract<T>::value)
					throw std::logic_error("The method or operation is not implemented.");
				else {
					return T::open();
				}
			}
			//	template<typename = std::enable_if<std::bool_constant<C>::value>::type>
			void close() {
				const char* name = strrchr(__FUNCTION__, ':') + 1;
				if (hasOwnProperty(name)) {
					//v8::Isolate* isolate = v8::Isolate::GetCurrent();

					//V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)

						/*v8::Local<v8::Object> o = object.Get(isolate);
						v8::Local<v8::Object> proto = o->GetPrototype()->ToObject(context).ToLocalChecked();

						v8::Local<v8::Value> value = proto->Get(context, V8_NEW_STRING_VAR(isolate, __FUNCTION__)).ToLocalChecked();

						auto f = v8::Local<v8::Function>::Cast(value);

						v8::Local<v8::Value> res = f->CallAsFunction(context, o, 0, {}).ToLocalChecked();*/

					v8::Local<v8::Value> value = call(name);

					value->BooleanValue(v8::Isolate::GetCurrent());

					//V8_CREATE_LOCAL_CONTEXT_END_WITH_RETURN(false)
				}
				if constexpr (std::is_abstract<T>::value)
					throw std::logic_error("The method or operation is not implemented.");
				else {
					T::close();
				}
			}
		};
	}
}
