#pragma once
#include "qevent.h"
#include "boost/core/noncopyable.hpp"

namespace shelllet {
	class Runnable
	{
	public:
		virtual	void run(QEvent* event) = 0;
	};
	

}