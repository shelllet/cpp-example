#pragma once

namespace shelllet::device {
	template<typename T, bool C>
	class QSerialPortInfoPrivate : public core::ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QSerialPortInfoPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}

		
	};
}
