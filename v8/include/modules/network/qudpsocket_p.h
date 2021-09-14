#pragma once
#include <QUdpSocket>
#include "qabstractsocket_p.h"

namespace shelllet::network {
	template<typename T, bool C>
	class QUdpSocketPrivate : public QAbstractSocketPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QUdpSocketPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QAbstractSocketPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
