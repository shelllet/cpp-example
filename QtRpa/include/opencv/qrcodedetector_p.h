#pragma once
namespace shelllet {
	namespace opencv {
		template<typename T, bool M>
		class QRCodeDetectorPrivate : public ObjectPrivate<T, M>
		{
		public:
			template<typename ...Args>
			QRCodeDetectorPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}

		};
	}
}
