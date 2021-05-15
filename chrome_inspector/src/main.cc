#include "framework.h"
#include <iostream>
#include "worker.h"
#include "logs.h"
#include "options_manager.h"
#include "native/global_implement.h"
#include <qapplication.h>
#include <qcommandlineparser.h>
#include <qcommandlineoption.h>
#include "native/global.h"

namespace shelllet {
	using namespace engine;
	using namespace global;
	class Application;
	class Event : public QEvent {
	public:
		static inline QEvent::Type Type = static_cast<QEvent::Type>(registerEventType());
		Event(const QString& file, bool inspect_brk)
			: QEvent(Type),
			file_(file),
			inspect_brk_(inspect_brk) {}
	private:
		QString file_;
		bool inspect_brk_;
		friend class Application;
	};
	class Application : public QApplication {
	public:
		Application(int& argc, char** argv) : QApplication(argc, argv) {
		}
	protected:
		void customEvent(QEvent* event) override
		{
			if (auto* e = dynamic_cast<Event*>(event)) {
				worker_->run(e->file_.toStdString(), e->inspect_brk_);
			}
		}
	private:
		std::unique_ptr<Worker> worker_ = std::make_unique<Worker>();
	};
}

int main(int argc, char* argv[])
{
#if defined(WIN32)
	if (CP_UTF8 != GetConsoleOutputCP())
		SetConsoleOutputCP(CP_UTF8);
#endif
	using namespace shelllet;
	Application app(argc, argv);
	QCoreApplication::setApplicationName("let");
	QCoreApplication::setApplicationVersion(MyGlobal::Version());
	QCoreApplication::setOrganizationName(MyGlobal::Version());
	//v8::V8::SetFlagsFromCommandLine(&argc, argv, true);

	QCommandLineParser parser;
	parser.setApplicationDescription(QObject::tr("A JavaScript engine that executes JavaScript (JS) code."));
	parser.addPositionalArgument("source", QObject::tr("Source file."));
	parser.addHelpOption();
	parser.addVersionOption();

	QCommandLineOption logLevel = { "level", QObject::tr("set logs level."), "error,warning",
#ifdef _DEBUG
		"trace"
#else
		"warning"
#endif // _DEBUG
	};
	QCommandLineOption moduleDir = { "modules-dir",
			QObject::tr("set modules dir."), "path", QString::fromStdString(options::options_manager::get_mutable_instance().options.modules_path.string()) };

	QCommandLineOption inspectBrk = { "inspect-brk",	QObject::tr("inspect break at js debug."), "boolean", "false" };

	parser.addOptions({ logLevel, moduleDir, 	inspectBrk });

	parser.process(app);

	const QStringList args = parser.positionalArguments();
	if (args.length() > 0) {
		logs::logger->initialize(logs::Logger::LevelFromString(parser.value(logLevel)));

		options::options_manager::get_mutable_instance().set_modules_path(parser.value(moduleDir));

		QCoreApplication::postEvent(&app, new Event(args[0], QVariant(parser.value(inspectBrk)).toBool()));
		return app.exec();
	}
	return EXIT_SUCCESS;
}