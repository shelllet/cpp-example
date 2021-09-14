#pragma once
#include "qiodevice_p.h"

namespace shelllet::core {
	template<typename T, bool C>
	class QFileDevicePrivate : public QIODevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QFileDevicePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QIODevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		QString fileName() const override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->fileName();
			}
			return __super::fileName();
		}
	};
}
