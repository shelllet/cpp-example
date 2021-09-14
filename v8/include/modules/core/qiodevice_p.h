#pragma once
#include "qobject_p.h"

namespace shelllet::core {
	template<typename T, bool C>
	class QIODevicePrivate : public QObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QIODevicePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		qint64 readData(char* data, qint64 maxlen) override
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		qint64 writeData(const char* data, qint64 len) override
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

		qint64 size() const override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->size();
			}
			return __super::size();
		}
	};
}
