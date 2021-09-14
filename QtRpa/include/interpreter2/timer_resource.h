#pragma once
#include "v8.hpp"
#include "resource.h"
#include <qtimer.h>

namespace shelllet {
	namespace resource {
		class TimerPrivate : public Resource {
		public:
			TimerPrivate(v8::Isolate* isolate, const v8::Local<v8::Function>& f);
		public:
			v8::Global<v8::Function> fn;
			std::unique_ptr<QTimer> timer;
			QMetaObject::Connection connection;
			void setTimeout(const std::function<void(TimerPrivate*)>& cb, uint64_t timeout);
			void clearTimeout();
			void setInterval(const std::function<void(TimerPrivate*)>& cb, uint64_t repeat);
			void clearInterval();
		protected:
			void cleanup() override;
		};
	}
}