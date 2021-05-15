#pragma once

namespace shelllet {
	namespace global {
		template<typename T, bool C>
		class MyConsolePrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			MyConsolePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
