#pragma once

namespace shelllet::random {
	template<typename T, bool C>
	class RandomDevicePrivate : public ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		RandomDevicePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		template<typename ... Args>
		RandomDevicePrivate(T* d, v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(d, std::forward<Args>(args)...) {
		}
	};
}
