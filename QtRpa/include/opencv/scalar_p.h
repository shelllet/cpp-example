#pragma once
namespace shelllet::opencv {
	template<typename T, bool C>
	class ScalarPrivate : public ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		ScalarPrivate(v8::Isolate* isoalte, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isoalte, obj, std::forward<Args>(args)...) {
		}
	};
}
