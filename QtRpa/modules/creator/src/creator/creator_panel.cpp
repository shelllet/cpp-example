#include <QCoreApplication>
#include <qtoolbar.h>
#include <qicon.h>
#include <qpalette.h>
#include <qdockwidget.h>
#include <qstandardpaths.h>
#include <qcoreapplication.h>
#include "creator.hpp"
#include "common.hpp"
#include "creator_panel.h"
#include <boost/asio/io_service.hpp>
#include <qprocess.h>
#include <qtextcodec.h>
#include "left_panel.h"
#include "view_panel.h"
#include "output_panel.h"
#include "creator/component.h"
#include "database/db.h"
#include "events/message_output_event.h"

namespace shelllet {

	namespace creator {
		class HideBar : public QWidget {

		public:
			QSize sizeHint() const override
			{
				return QSize(0, 0);
			}


			QSize minimumSizeHint() const override
			{
				return QSize(0, 0);
			}
			~HideBar() { LOG_DEBUG("rpa") << "# ~HideBar." << std::endl; }
		};
	}
}


shelllet::creator::CreatorPanel::CreatorPanel(QWidget* parent)
	: QMainWindow(parent, Qt::Widget)
{
	//addAndMakeVisible(toolbar_);
	/*QPalette pal;
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);*/
	auto* toolbar = addToolBar("action");
	toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	toolbar->addAction(Environment::getInstance()->getIconByName("new"), "new", [this]() { New::messageCallback(this); });
	toolbar->addAction(Environment::getInstance()->getIconByName("open"), "open", [this]() { Open::messageCallback(this); });
	toolbar->addAction(Environment::getInstance()->getIconByName("save"), "save", [this]() { Save::messageCallback(this); });
	toolbar->addAction(Environment::getInstance()->getIconByName("exec"), "exec", [this]() { Exec::messageCallback(this); });
	toolbar->addAction(Environment::getInstance()->getIconByName("about"), "about", [this]() { About::messageCallback(this); });
	//toolbar->addAction(QIcon(":/new/toolbar/assets/icons/help.svg"）, "new", this, &New::messageCallback);

	//addAndMakeVisible(m_right);

	//getTopLevelComponent()->addKeyListener(global::global_command::get_mutable_instance().getKeyMappings());

	/*m_explorer.onDoubleClicked = std::bind(&component_right_project::openTab,
		&m_right, std::placeholders::_1);*/

		/*m_right.addListener(std::bind(&project::component_explorer_project::handleContentChangedEvent,
		  std::ref(m_explorer), std::placeholders::_1, std::placeholders::_2));*/

		  //global::global_event::get_mutable_instance().connect_files_dropped(std::bind(&component_content_project::fileDrops,
		  //	this, std::placeholders::_1));


	panel[0] = new HideBar;
	panel[1] = new HideBar;
	panel[2] = new HideBar;

	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	//setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
	//setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);

	QDockWidget* leftDock = new QDockWidget("", this);
	leftDock->setAllowedAreas(Qt::LeftDockWidgetArea);
	leftDock->setWidget(new LeftPanel);
	leftDock->setTitleBarWidget(panel[0]);
	leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::LeftDockWidgetArea, leftDock);

	QDockWidget* rightDock = new QDockWidget("", this);
	rightDock->setAllowedAreas(Qt::RightDockWidgetArea);
	rightDock->setWidget(new properties_component);
	rightDock->setTitleBarWidget(panel[1]);
	rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::RightDockWidgetArea, rightDock);

	setCentralWidget(new ViewPanel(this));

	QDockWidget* bottomDock = new QDockWidget("", this);
	bottomDock->setAllowedAreas(Qt::BottomDockWidgetArea);
	bottomDock->setWidget(new OutputPanel);
	bottomDock->setTitleBarWidget(panel[2]);
	bottomDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::BottomDockWidgetArea, bottomDock);
}

shelllet::creator::CreatorPanel::~CreatorPanel()
{
	qDeleteAll(panel);
}

void shelllet::creator::CreatorPanel::callbk(shelllet::creator::CallbackMessage* callback, int num, ...)
{
	va_list arguments;
	va_start(arguments, num);
	QList<QWidget*> widgets;

	for (auto* dock : findChildren<QDockWidget*>()) {
		widgets.append(dock->widget());
	}

	widgets.append(centralWidget());

	if (dynamic_cast<Open*>(callback) != nullptr ||
		dynamic_cast<New*>(callback) != nullptr) {
		Path currentFile = va_arg(arguments, Path);
		common::Environment::getInstanceRef()->setCurrentFilePath(currentFile);
		for (auto w : widgets)
		{
			if (auto* serialization = dynamic_cast<common::Serialization*>(w))
			{
				serialization->load(common::Environment::getInstance()->indexXmlPath());
			}
		}
	}
	else if (dynamic_cast<Save*>(callback) != nullptr)
	{
		for (auto w : widgets)
		{
			if (auto* serialization = dynamic_cast<common::Serialization*>(w)) {
				if (!Environment::getInstance()->getCurrentProjectPath().isEmpty())
					serialization->save(Environment::getInstance()->getCurrentProjectPath());
			}
		}
	}
	else if (dynamic_cast<Exec*>(callback) != nullptr) {
		std::thread t([this]() { exec(); });
		t.detach();
	}

	va_end(arguments);
}

void shelllet::creator::CreatorPanel::exec()
{

	QProcess process;
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

	process.setProcessEnvironment(env);
	connect(&process, &QProcess::readyReadStandardError, [&]() {
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % codec->toUnicode(process.readAllStandardError()).toStdString();
		QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
	});

	connect(&process, &QProcess::readyReadStandardOutput, [&]() {
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % codec->toUnicode(process.readAllStandardOutput()).toStdString();
		QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
	});

	connect(&process, &QProcess::errorOccurred, [&](QProcess::ProcessError error) {
		if (error == QProcess::FailedToStart) {
			auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % "failed to start";
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
		}
		else if (error == QProcess::Crashed) {
			auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % "crash";
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
		}
		else if (error == QProcess::Timedout) {
			auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % "timeout";
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
		}
		else if (error == QProcess::ReadError) {
			auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % "read error";
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
		}
		else {
			auto fmt = boost::format("[%1%]: %2%") % Environment::getInstance()->getCurrentProjectPath() % "unknown error";
			QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
		}
	});

	connect(&process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
		[&](int, QProcess::ExitStatus exitStatus) {
		auto fmt = boost::format("[%1%]: exit with %2%") % Environment::getInstance()->getCurrentProjectPath() % exitStatus;
		QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent(fmt.str()));
	}
	);

	process.start(QCoreApplication::applicationFilePath(), { "--interpreter=true", *Environment::getInstance()->getCurrentProjectPath().toString().toQString() });
	process.waitForFinished(-1);
	QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::MessageOutputEvent("#->Exit."));
}

void shelllet::creator::CreatorPanel::git()
{
}

void shelllet::creator::CreatorPanel::create()
{
	New::messageCallback(this);
}

void shelllet::creator::CreatorPanel::open()
{
	Open::messageCallback(this);
}