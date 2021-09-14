#pragma once
#include <QWebSocketServer>
#include "qobject_p.h"

namespace shelllet::network {
	template<typename T, bool C>
	class QWebSocketServerPrivate : public core::QObjectPrivate<T, C>
	{
	public:
		template<typename ... Args>
		QWebSocketServerPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
