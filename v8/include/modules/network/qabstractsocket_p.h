#pragma once
#include <QAbstractSocket>
#include "qiodevice_p.h"

namespace shelllet::network {
	template<typename T, bool C>
	class QAbstractSocketPrivate : public core::QIODevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QAbstractSocketPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QIODevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
