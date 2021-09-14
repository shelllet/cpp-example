#pragma once
#include <QNetworkDatagram>

namespace shelllet::network {
	template<typename T, bool C>
	class QNetworkDatagramPrivate : public core::ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QNetworkDatagramPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
