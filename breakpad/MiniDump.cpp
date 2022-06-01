#include "pch.h"
#include "MiniDump.h"
#include "winrt/Simple.h"
#include "Model/LevelDB.h"
//#include "TaskForground.h"
//#include "App.xaml.h"
using namespace winrt;
using namespace winrt::Simple;

using namespace google_breakpad;

namespace net::winui {

	static void Client_ConnectedCallback(void* context, const google_breakpad::ClientInfo* client_info) {
		LOG_INFO << "# connected." << std::endl;
	}

	static void Client_ExitedCallback(void* context, const google_breakpad::ClientInfo* client_info) {
		LOG_INFO << "# exit." << std::endl;
		// temp resolve.
		//Application::Current().as<App>()->TaskForground()->Stop();
	}
	void Client_UploadRequestCallback(void* context, const DWORD crash_id) {

	}
	bool FilterCallback(void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion)
	{
		return true;
	}

	bool MinidumpCallback(const wchar_t* dump_path, const wchar_t* minidump_id, void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool succeeded) {
		MiniDump* p = static_cast<MiniDump*>(context);

		if (p->exception_handler->IsOutOfProcess())
			return p->exception_handler->RequestUpload(0);
		return succeeded;
	}

	MiniDump::MiniDump(hstring const& dumpPath, hstring const& name) {
		std::filesystem::path p = std::wstring(dumpPath);

		if (!std::filesystem::exists(p /= "dump")) {
			std::filesystem::create_directories(p);
		}

	}

	MiniDump::~MiniDump()
	{

	}

	bool MiniDump::startCrashServer() {
		if (crash_server) {
			return true;
		}

		crash_server = new google_breakpad::CrashGenerationServer(std::wstring(m_info.second),
			nullptr,
			Client_ConnectedCallback,
			nullptr,
			[](void* /*context*/, const google_breakpad::ClientInfo* /*client_info*/, const std::wstring* /*dump_path*/) {

			},
			nullptr,
				Client_ExitedCallback,
				nullptr,
				Client_UploadRequestCallback,
				this,
				false,
				nullptr);


		if (!crash_server->Start()) {
			reset();
			return false;
		}
		return true;
	}

	void MiniDump::stopCrashServer() {
		reset();
	}

	void MiniDump::reset()
	{
		delete crash_server;
		crash_server = nullptr;
	}

	void MiniDump::StartClient()
	{
		google_breakpad::CustomClientInfo custom_info = {  };

		exception_handler = std::make_unique<ExceptionHandler>(std::wstring(m_info.first),
			FilterCallback, MinidumpCallback, this, ExceptionHandler::HandlerType::HANDLER_ALL, MiniDumpNormal, m_info.second.c_str(), &custom_info);
#ifdef _DEV
		exception_handler->set_handle_debug_exceptions(true);
#endif // _DEBUG
	}
}