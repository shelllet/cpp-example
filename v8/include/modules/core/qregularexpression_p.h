#pragma once

namespace shelllet::core {
	template<typename T, bool C>
	class RegularExpressionPrivate : public ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		RegularExpressionPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}

		
	};
}
