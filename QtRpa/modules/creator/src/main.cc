#include "common.hpp"
#include "creator.hpp"
#include "events.hpp"
#include <iostream>
#include "interpreter.hpp"
#include "creator/application.h"
#include <qapplication.h>
#include <qcommandlineparser.h>
#include <qcommandlineoption.h>
#include <qstandardpaths.h>
#include <qdatetime.h>
//#include <qplugin.h>
#include "qmessagebox.h"
#include "boost/scope_exit.hpp"
#include "creator/gui_application.h"
#include "qprocess.h"

#ifdef Q_OS_WIN32
#include "client/windows/common/ipc_protocol.h"
#include "client/windows/handler/exception_handler.h"
#endif // Q_OS_WIN32

#include "creator/mini_dump.h"
#include "creator/dump_dialog.h"

//Q_IMPORT_PLUGIN(QSvgPlugin)

namespace shelllet {
	std::unique_ptr<google_breakpad::ExceptionHandler> exception_handler;

	using namespace creator;

	void Run_ChildConsole(severity_level level, const std::filesystem::path& file, bool inspect) {
		Logger::getInstance()->addFileSink(level, common::Environment::getInstance()->logsPath() / "console.log");
		Logger::getInstance()->initialize();
		QCoreApplication::postEvent(qApp, new ConsoleEvent(file, inspect));
	}
	void Run_ChildGui(severity_level level) {
		Logger::getInstance()->addFileSink(level, common::Environment::getInstance()->logsPath() / "rpa.log");
		Logger::getInstance()->initialize();

		QCoreApplication::postEvent(qApp, new GuiEvent);
	}


	void Run_MainProcess(QProcess& process) {

		Logger::getInstance()->addFileSink(info, common::Environment::getInstance()->logsPath() / "main.log");
		Logger::getInstance()->initialize();
		process.start(QCoreApplication::applicationFilePath(), QCoreApplication::arguments());

		QObject::connect(&process, &QProcess::errorOccurred, [&](QProcess::ProcessError error) {
			LOG_INFO("rpa") << "# error occurred: " << process.errorString().toStdString() << std::endl;
			//qApp->quit();
		});
		QObject::connect(&process, qOverload<int, QProcess::ExitStatus>(&QProcess::finished), [](int exitCode, QProcess::ExitStatus exitStatus) {
			LOG_INFO("rpa") << "# app exit." << std::endl;
			//qApp->quit();
		});
	}

	void Run_Child(Application& application) {
		google_breakpad::CustomClientInfo custom_info = {  };

		exception_handler = std::make_unique<google_breakpad::ExceptionHandler>(common::Environment::getInstance()->dumpPath().wstring(),
			nullptr, [](const wchar_t* dump_path, const wchar_t* minidump_id, void* context, EXCEPTION_POINTERS* exinfo, MDRawAssertionInfo* assertion, bool succeeded)
		{
			if (exception_handler->IsOutOfProcess())
				return exception_handler->RequestUpload(0);
			return succeeded;
		}
			, nullptr
			, google_breakpad::ExceptionHandler::HandlerType::HANDLER_ALL
			, MiniDumpNormal, common::Environment::getInstance()->getOptions()->pipe_name.toStdWString().c_str(),
			&custom_info);

		exception_handler->set_handle_debug_exceptions(true);

		application.setQuitOnLastWindowClosed(true);


		QCommandLineParser parser;
		parser.setApplicationDescription(QObject::tr("Robotic process automation"));
		parser.addPositionalArgument("source", QObject::tr("Source file."));
		parser.addHelpOption();
		parser.addVersionOption();

		QCommandLineOption logLevel = { "level", QObject::tr("logs level."), "error, warning ...",
	#ifdef _DEBUG
			"trace"
	#else
			"warning"
	#endif // _DEBUG
		};
		QCommandLineOption moduleDir = { "modules-dir",
				QObject::tr("set modules dir."), "path", QString::fromStdString(common::Environment::getInstance()->getOptions()->modules_path.string()) };

		QCommandLineOption inspectBrk = { "inspect-brk",	QObject::tr("inspect break at js debug."), "boolean", "false" };

		QCommandLineOption is_console = { "interpreter",	QObject::tr("interpreter."), "boolean", "false" };

		parser.addOptions({ logLevel, moduleDir, 	inspectBrk,is_console });

		parser.process(*application.toQApplication());

		const QStringList args = parser.positionalArguments();

		common::Environment::getInstanceRef()->setModulePath(parser.value(moduleDir));

		if (parser.isSet(is_console)) {
			Run_ChildConsole(Logger::levelFromString(parser.value(logLevel).toStdString()), args[0].toStdString(), QVariant(parser.value(inspectBrk)).toBool());
		}
		else {
			Run_ChildGui(Logger::levelFromString(parser.value(logLevel).toStdString()));

		}
	}
}
int main(int argc, char* argv[])
{
	using namespace shelllet;
	_CrtSetReportMode(_CRT_ASSERT, 0);
	//Q_INIT_RESOURCE(creator);
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QGuiApplication::setApplicationName("let");
	QGuiApplication::setApplicationVersion("0.5.0");
	QGuiApplication::setOrganizationName("shelllet");
	QGuiApplication::setOrganizationDomain("shelllet.com");
	Application application(argc, argv);
	std::filesystem::create_directories(common::Environment::getInstance()->logsPath());
	std::filesystem::create_directories(common::Environment::getInstance()->dumpPath());
	application.setWindowIcon(QIcon(*(Environment::getInstance()->getAssetsPath() / "icons/favicon.png").toString().toQString()));

	QProcess process;
#ifndef _DEBUG
	debug::MiniDump mini;
	if (mini.startCrashServer(common::Environment::getInstance()->dumpPath())) {
		Run_MainProcess(process);
	}
	else {
#endif // !_DEBUG
		Run_Child(application);
#ifndef _DEBUG
	}
	BOOST_SCOPE_EXIT(&mini) {
		mini.stopCrashServer();
	}BOOST_SCOPE_EXIT_END
#endif // !_DEBUG

		QApplication::exec();
	//worker.reset();
	return EXIT_SUCCESS;
}