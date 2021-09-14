#pragma once
#include "qiodevice_p.h"

namespace shelllet::core {
	template<typename T, bool C>
	class QProcessPrivate : public QIODevicePrivate<T, C>
	{
	public:
		template<typename ...Args>
		QProcessPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QIODevicePrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		template<typename ... Args>
		QProcessPrivate(T* d, v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QIODevicePrivate(d, std::forward<Args>(args)...) {
		}
		void setupChildProcess() override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->setupChildProcess();
			}
			return __super::setupChildProcess();
		}
	};
}
