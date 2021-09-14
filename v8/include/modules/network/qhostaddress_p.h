#pragma once

namespace shelllet::network {
	template<typename T, bool C>
	class QHostAddressPrivate : public core::ObjectPrivate<T, C>
	{
	public:
		template<typename ... Args>
		QHostAddressPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
