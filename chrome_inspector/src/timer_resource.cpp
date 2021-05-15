#include <qtimer.h>
#include "timer_resource.h"
#include "native/global_implement.h"

namespace shelllet {
	using namespace global;
}
shelllet::resource::TimerPrivate::TimerPrivate(v8::Isolate* isolate, const v8::Local<v8::Function>& f)
	: fn(isolate, f)
{
}

void shelllet::resource::TimerPrivate::setTimeout(const std::function<void(TimerPrivate*)>& cb, uint64_t timeout)
{
	timer = std::make_unique<QTimer>();
	connection = timer->callOnTimeout([this, cb]() {
		cb(this);
		});
	timer->setSingleShot(true);
	timer->setTimerType(Qt::CoarseTimer);
	timer->start(timeout);
}

void shelllet::resource::TimerPrivate::clearTimeout()
{
	timer->stop();
	timer->disconnect(connection);
}

void shelllet::resource::TimerPrivate::setInterval(const std::function<void(TimerPrivate*)>& cb, uint64_t repeat)
{
	timer = std::make_unique<QTimer>();
	connection = timer->callOnTimeout([this, cb]() {
		cb(this);
		});
	timer->setSingleShot(false);
	timer->setInterval(repeat);
	timer->setTimerType(Qt::CoarseTimer);
	timer->start();
}

void shelllet::resource::TimerPrivate::clearInterval()
{
	timer->stop();
	timer->disconnect(connection);
}

void shelllet::resource::TimerPrivate::cleanup()
{
	clearTimeout();
	clearInterval();
	fn.Reset();
}