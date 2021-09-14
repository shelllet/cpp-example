#pragma once

namespace shelllet {
	namespace widgets {
		template<typename T, bool C>
		class WidgetPrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			WidgetPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
