#pragma once
#include <QTcpServer>
#include "qobject_p.h"

namespace shelllet::network {
	template<typename T, bool C>
	class QTcpServerPrivate : public core::QObjectPrivate<T, C>
	{
	public:
		QTcpServerPrivate() {
		}
	};
}
