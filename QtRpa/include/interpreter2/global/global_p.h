#pragma once
namespace shelllet::global {
	template<typename T, bool C = true>
	class MyGlobalPrivate : public V8ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		MyGlobalPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : V8ObjectPrivate<T, C>(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
