#pragma once

namespace shelllet {
	namespace core {
		template<typename T, bool C>
		class QRectPrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QRectPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}

		};
	}
}
