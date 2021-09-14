#pragma once
#include <QTcpSocket>
#include "qabstractsocket_p.h"

namespace shelllet::network {
	template<typename T, bool C>
	class QTcpSocketPrivate : public QAbstractSocketPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QTcpSocketPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) :QAbstractSocketPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
