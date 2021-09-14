#pragma once
namespace shelllet {
	namespace gui {
		template<typename T, bool C>
		class QColorPrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QColorPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}