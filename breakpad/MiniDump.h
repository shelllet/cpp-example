#pragma once

namespace net::winui {
	struct MiniDump : implements<MiniDump, IInspectable>
	{
		google_breakpad::CrashGenerationServer* crash_server = nullptr;

		std::unique_ptr<google_breakpad::ExceptionHandler> exception_handler;

		std::pair<winrt::hstring, winrt::hstring> m_info;

		MiniDump(winrt::hstring const& dumpPath, winrt::hstring const& name);
		~MiniDump();

		void StartClient();
		bool startCrashServer();
		void stopCrashServer();


		void reset();
	
	};

}