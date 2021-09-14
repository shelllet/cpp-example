#pragma once
#include "framework.h"
#include <QTcpSocket>
#include "qabstractsocket_wrapper.h"

namespace shelllet {
	namespace network {
		template<typename T, bool> class QTcpSocketPrivate;
		template<typename T, typename U, bool C>
		class QTcpSocketWrapper : public QAbstractSocketWrapper<T, U, C> {
		public:
			template<bool M>
			QTcpSocketWrapper(QTcpSocketPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
				: QAbstractSocketWrapper(d, args)
			{
			}

			QTcpSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QAbstractSocketWrapper(isolate, tpl) {}
			QTcpSocketWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QAbstractSocketWrapper(isolate, proto) {}

		private:
		};
	}
}
