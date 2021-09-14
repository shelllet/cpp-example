#include <qapplication.h>
#include <qtimer.h>
#include <iostream>
#include "interpreter/consoleapplication.h"
#include "interpreter/inspector_agent.h"
#include "interpreter/tcp_server.h"
#include "common.hpp"
#include "properties.hpp"
#include "events/common_event.h"
namespace shelllet {
	using namespace inspect;
	using namespace interpreter;
	extern std::string FrontendUrl(const std::string& address, uint16_t port);

	namespace interpreter {
		class ConsoleApplicationPrivate {
		public:
			std::unique_ptr<InspectorAgent> agent_;
			std::unique_ptr<v8::Platform> platform_;
			inspect::TcpServer* worker_thread_ = nullptr;
		};


	}
}

shelllet::inspect::InspectorVersion shelllet::interpreter::ConsoleApplication::requestInspectorVersion()
{
	return { "1.2","v8inspector" };
}

shelllet::inspect::InspectorList shelllet::interpreter::ConsoleApplication::requestInspectorList()
{
	return {
		"v8inspector instance",
		"node",
		"Debug",
		"file:///",
		"127.0.0.1",
		9229
	};
}

shelllet::interpreter::ConsoleApplication::ConsoleApplication()
//: d_ptr(new ConsoleApplicationPrivate)
	: p_(new ConsoleApplicationPrivate)
{
#ifdef _DEBUG
	v8::V8::SetFlagsFromString("--expose-gc");
#endif // _DEBUG
	v8::V8::InitializeICUDefaultLocation(__argv[0]);
	v8::V8::InitializeExternalStartupData(__argv[0]);

	d_func()->platform_ = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(d_func()->platform_.get());
	v8::V8::Initialize();

	Helper::register_meta_type();
}

shelllet::interpreter::ConsoleApplication::~ConsoleApplication()
{
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
	delete p_;
}


void shelllet::interpreter::ConsoleApplication::run(QEvent* event)
{
	events::ConsoleEvent* e = dynamic_cast<events::ConsoleEvent*>(event);

	if (!std::filesystem::exists(e->filename())) {
		LOG_ERROR("engine") << "# the file not exist: " << e->filename();
		return;
	}

	if (e->inspectBrk()) {
		d_func()->worker_thread_ = new TcpServer(this, QHostAddress::LocalHost, 9229);
		connect(d_func()->worker_thread_, &TcpServer::finished, d_func()->worker_thread_, &QObject::deleteLater);
		d_func()->worker_thread_->start();
		auto info = requestInspectorList();
		std::cout << "# debugger connection success; copy URL and open in Chrome browser: " << FrontendUrl(info.address, info.port) << std::endl;
	}

	d_func()->agent_ = std::make_unique<InspectorAgent>(this, d_func()->platform_.get(), e->filename(), e->inspectBrk());
	d_func()->agent_->run();
}




void shelllet::interpreter::ConsoleApplication::finished()
{
	if (d_func()->worker_thread_ && d_func()->worker_thread_->isRunning()) {
		d_func()->worker_thread_->requestInterruption();
		d_func()->worker_thread_->wait();
	}
}

void shelllet::interpreter::ConsoleApplication::customEvent(QEvent* event)
{
	if (auto* e = dynamic_cast<MessageInEvent*>(event)) {
		d_func()->agent_->postInspectorMessage(QString::fromStdString(e->message));
	}
	else if (auto* e = dynamic_cast<MessageOutEvent*>(event)) {
		dispatchInspectorMessage(e->message);
	}
	else if (auto* e = dynamic_cast<ContinueRunEvent*>(event)) {
		d_func()->agent_->evaluate();
		d_func()->agent_->cleanup();
		finished();
		QCoreApplication::removePostedEvents(this);
		QTimer::singleShot(100, qApp, [this]() {
			d_func()->agent_.reset(nullptr);
			QCoreApplication::quit();
		});
		QCoreApplication::processEvents();
		LOG_TRACE("inspect") << "# evaluate end." << std::endl;
	}
	else if (auto* e = dynamic_cast<PumpMessageLoopEvent*>(event)) {
		d_func()->agent_->pumpMessageLoop();
	}

	else if (auto* e = dynamic_cast<DisconnectEvent*>(event)) {
		d_func()->agent_->disconnectInspector();
	}
}