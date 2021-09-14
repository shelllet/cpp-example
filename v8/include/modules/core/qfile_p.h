#pragma once
#include <qfile.h>
#include "qfiledevice_p.h"

namespace shelllet::core {
	template<typename T, bool C>
	class QFilePrivate : public QFileDevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QFilePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QFileDevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
	};
}
