#pragma once
namespace shelllet {
	namespace core {
		template<typename T, bool C>
		class QTimerPrivate : public QObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QTimerPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
