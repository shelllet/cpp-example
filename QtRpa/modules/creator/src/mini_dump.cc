#include "creator.hpp"
#include "string"
#include "client/windows/crash_generation/crash_generation_server.h"
#include "client/windows/common/ipc_protocol.h"
#include "client/windows/crash_generation/client_info.h"

#include "qcoreapplication.h"
#include "qcommandlineparser.h"
#include "creator/mini_dump.h"
#include "creator/dump_dialog.h"
#include "private/qobject_p.h"
#include "events/common_event.h"

namespace shelllet {
	class MiniDumpPrivate : public QObjectPrivate {
	public:
		google_breakpad::CrashGenerationServer* crash_server = nullptr;
		std::mutex cv_m;
		std::condition_variable cv;

		void reset() {
			delete crash_server;
			crash_server = nullptr;
		}

	};
	;
	class Runner : public Runnable {
	public:
		Runner(std::condition_variable& cv) : cv(cv) {}
		void run(QEvent* event) override
		{
			dialog = new creator::DumpDialog;
			dialog->show();

			QObject::connect(dialog, &creator::DumpDialog::finished, [this](int) {
				cv.notify_one();
				});
		}
		~Runner()
		{
			QMetaObject::invokeMethod(dialog, "deleteLater", Qt::QueuedConnection);
		}
	private:
		std::condition_variable& cv;
		creator::DumpDialog* dialog = nullptr;
	};

	static void Client_ConnectedCallback(void* context, const google_breakpad::ClientInfo* client_info) {
		LOG_INFO("rpa") << "# connected." << std::endl;
	}

	static void Client_ExitedCallback(void* context, const google_breakpad::ClientInfo* client_info) {
		LOG_INFO("rpa") << "# exit." << std::endl;
	}
	void Client_UploadRequestCallback(void* context, const DWORD crash_id) {
		MiniDumpPrivate* d = static_cast<MiniDumpPrivate*>(context);
		std::unique_ptr<Runner> p = std::make_unique<Runner>(d->cv);
		QCoreApplication::postEvent(qApp, new events::DumpRequestEvent(p.get()));

		std::unique_lock<std::mutex> lk(d->cv_m);
		d->cv.wait(lk);
	}
}

shelllet::debug::MiniDump::MiniDump(QObject* parent /*= nullptr*/) : QObject(*new MiniDumpPrivate, parent)
{

}

shelllet::debug::MiniDump::~MiniDump()
{

}

bool shelllet::debug::MiniDump::startCrashServer(const std::wstring& dump_path) {
	Q_D(MiniDump);
	if (d->crash_server) {
		return true;
	}

	d->crash_server = new google_breakpad::CrashGenerationServer(common::Environment::getInstance()->getOptions()->pipe_name.toStdWString().c_str(),
		nullptr,
		Client_ConnectedCallback,
		nullptr,
		[](void* /*context*/, const google_breakpad::ClientInfo* /*client_info*/, const std::wstring* /*dump_path*/) {

		},
		nullptr,
			Client_ExitedCallback,
			nullptr,
			Client_UploadRequestCallback,
			d,
			true,
			&dump_path);


	if (!d->crash_server->Start()) {
		d->reset();
		return false;
	}
	return true;
}

void shelllet::debug::MiniDump::stopCrashServer() {
	Q_D(MiniDump);
	d->reset();
}