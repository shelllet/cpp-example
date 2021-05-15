#include <qapplication.h>
#include "framework.h"
#include <qtimer.h>
#include <iostream>
#include "worker.h"
namespace shelllet {
	using namespace inspect;
	extern std::string FrontendUrl(const std::string& address, uint16_t port);
}

shelllet::inspect::InspectorVersion shelllet::engine::Worker::requestInspectorVersion()
{
	return { "1.2","v8inspector" };
}

shelllet::inspect::InspectorList shelllet::engine::Worker::requestInspectorList()
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

shelllet::engine::Worker::Worker()
{
#ifdef _DEBUG
	v8::V8::SetFlagsFromString("--expose-gc");
#endif // _DEBUG
	v8::V8::InitializeICUDefaultLocation(__argv[0]);
	v8::V8::InitializeExternalStartupData(__argv[0]);

	platform_ = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(platform_.get());
	v8::V8::Initialize();
}

shelllet::engine::Worker::~Worker()
{
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}

void shelllet::engine::Worker::run(const std::string& filename, bool inspect_brk)
{
	if (!std::filesystem::exists(filename)) {
		LOG_ERROR("engine") << "# the file not exist: " << filename;
		return;
	}

	std::filesystem::path src = filename;
	std::filesystem::path dir = src.parent_path();
	if (std::filesystem::is_directory(src)) {
		dir = src;
		src /= "src/index.js";
	}
	std::string name = src.filename().string();

	std::ifstream stream(src);
	std::string code = std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

	if (inspect_brk) {
		worker_thread_ = new TcpServer(this, QHostAddress::LocalHost, 9229);
		connect(worker_thread_, &TcpServer::finished, worker_thread_, &QObject::deleteLater);
		worker_thread_->start();
		auto info = requestInspectorList();
		std::cout << "# debugger connection success; copy URL and open in Chrome browser: " << FrontendUrl(info.address, info.port) << std::endl;
	}

	agent_ = std::make_unique<InspectorAgent>(this, platform_.get(), name, code, dir.string(), inspect_brk);
	agent_->run();
}

void shelllet::engine::Worker::finished()
{
	if (worker_thread_ && worker_thread_->isRunning()) {
		worker_thread_->requestInterruption();
		worker_thread_->wait();
	}
}

void shelllet::engine::Worker::customEvent(QEvent* event)
{
	if (auto* e = dynamic_cast<MessageInEvent*>(event)) {
		agent_->postInspectorMessage(QString::fromStdString(e->message));
	}
	else if (auto* e = dynamic_cast<MessageOutEvent*>(event)) {
		dispatchInspectorMessage(e->message);
	}
	else if (auto* e = dynamic_cast<ContinueRunEvent*>(event)) {
		agent_->evaluate();
		agent_->cleanup();
		finished();
		QCoreApplication::removePostedEvents(this);
		QTimer::singleShot(100, qApp, [this]() {
			agent_.reset(nullptr);
			QCoreApplication::quit();
			});
		QCoreApplication::processEvents();
		LOG_TRACE("inspect") << "# evaluate end." << std::endl;
	}
	else if (auto* e = dynamic_cast<PumpMessageLoopEvent*>(event)) {
		agent_->pumpMessageLoop();
	}

	else if (auto* e = dynamic_cast<DisconnectEvent*>(event)) {
		agent_->disconnectInspector();
	}
}