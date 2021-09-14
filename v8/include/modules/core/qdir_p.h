#pragma once
namespace shelllet {
	namespace core {
		template<typename T, bool M>
		class QDirPrivate : public ObjectPrivate<T, M>
		{
		public:
			template<typename ...Args>
			QDirPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}

		};
	}
}
