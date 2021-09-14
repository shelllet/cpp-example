#include "common.hpp"
#include "view_panel.h"
#include <QPushButton>
#include "events/common_event.h"
#include "events/listener_manager.h"

#pragma warning(disable: 4996)
#include <yaml-cpp/yaml.h>
#include "tabitem_page.h"
#include "events/file_browser_event.h"

namespace shelllet {
	using namespace events;
}
using namespace shelllet::creator;

ViewPanel::ViewPanel(QWidget* parent)
	: QTabWidget(parent)
{
	using namespace events;

	//activity_deleted_event::get_mutable_instance().connect([&]() { resized(); });
	//activity_created_event::get_mutable_instance().connect([&]() { resized(); });
	//searchWidget = new ActivitiesSearchWidget(this);

	events::EventDispatcher::Dispatcher()->push(this);
	auto* button = new QPushButton("additional", this);

	connect(button, &QPushButton::clicked, [this]() {
		auto xy = mapToGlobal(QPoint(0, 0));
		//searchWidget->setGeometry(QRect(xy, QSize(geometry().width(), geometry().height() / 3 * 2)));
		//searchWidget->show();
		});

	setCornerWidget(button, Qt::TopLeftCorner);
}

ViewPanel::~ViewPanel()
{
}

bool shelllet::creator::ViewPanel::tabOpened(const QString& tab) const
{
	for (auto i = 0; i < count(); ++i) {
		if (tab == tabText(i)) {
			return true;
		}
	}
	return false;
}

void shelllet::creator::ViewPanel::customEvent(QEvent* event)
{
	if (event->type() == events::ActivitiesShowEvent::eType) {
		auto xy = mapToGlobal(QPoint(0, 0));
		searchWidget->setGeometry(QRect(xy, QSize(geometry().width(), geometry().height() / 3 * 2)));
		searchWidget->show();
	}
	else if (event->type() == events::FileBrowserEvent::Type) {
		auto* e = dynamic_cast<events::FileBrowserEvent*>(event);

		if (!tabOpened(QString::fromStdString(e->getFileName().string()))) {
			openTab(e->filePath());
		}
	}
}

void ViewPanel::create()
{
	//String name = std::filesystem::path(db->getFilename()).filename().c_str();
	//auto* view = new TabTreeView(signal_, db, "main.xml");
	//view->create(db);
	//addTab("main.xml", juce::Colours::darkgrey, view, true);
}

void ViewPanel::load(const Path& filename)
{
	openTab(filename);
}

void shelllet::creator::ViewPanel::openTab(const Path& filename)
{
	common::Serialization* s = nullptr;
	//if (filename.extension() == ".js") {
		//s = new ScintillaPage(std::filesystem::relative(filename, currentDir_), this);
	//}
//	else if (filename.extension() == ".xml") {
	s = new TabItemPage(this);
	//	}
	s->load(filename);

	addTab(dynamic_cast<QWidget*>(s), *filename.toString().toQString());
}

void ViewPanel::save(const Path& filename)
{
	for (auto i = 0; i < count(); i++)
	{
		auto c = dynamic_cast<common::Serialization*>(widget(i));
		auto p = dynamic_cast<common::Property*>(widget(i));

		c->save(filename);
	}
}