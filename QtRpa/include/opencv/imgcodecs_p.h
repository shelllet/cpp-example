#pragma once
namespace shelllet::opencv {
	template<typename T, bool C>
	class ImgCodecsPrivate : public ObjectPrivate<T, C>
	{

	public:
		template<typename ...Args>
		ImgCodecsPrivate(v8::Isolate* isoalte, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isoalte, obj, std::forward<Args>(args)...) {
		}
	};
}

