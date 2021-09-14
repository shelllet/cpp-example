#pragma once
namespace shelllet::opencv {
	template<typename T, bool C>
	class ImgProcPrivate : public ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		ImgProcPrivate(v8::Isolate* isoalte, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isoalte, obj, std::forward<Args>(args)...) {
		}
	};
}
