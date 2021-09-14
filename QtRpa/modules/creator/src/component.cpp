#include <QVBoxLayout>
#include "property.hpp"
#include "interpreter.hpp"
#include "creator/component.h"
#include "events/activity_select_event.h"
#include "events/common_event.h"

shelllet::creator::properties_component::properties_component(QWidget* parent)
	: QWidget(parent)
{
	auto* layout = new QVBoxLayout;
	browser_ = new PropertyBrowser(this);
	layout->addWidget(browser_);
	setLayout(layout);

	events::EventDispatcher::Dispatcher()->push(this);
}

shelllet::creator::properties_component::~properties_component()
{
}

///void properties_component::updateProperty(const std::shared_ptr<properties::UniqueNamedProperty>& property)
//{
	//String name = property->getUniqueName();

	//if (global_activities.count(name.toRawUTF8()))
	//{
		//display_.reset(global_activities[name.toRawUTF8()](db_, property));

		//display_->display();
	//}
//}

void shelllet::creator::properties_component::variable_changed(int action, const std::string& old_name, const std::string& new_name)
{
	//display_->variable_changed(action, old_name, new_name);
}

void shelllet::creator::properties_component::customEvent(QEvent* event)
{
	if (event->type() == events::ActivitySelectEvent::Type) {
		auto* e = dynamic_cast<events::ActivitySelectEvent*>(event);

		browser_->clear();

		auto p = e->getProp();
		if (p) {
			for (auto* prop : p->getProp(browser_)) {
				if (prop)
					browser_->addProperty(prop);
			}
		
			browser_->addProperty(e->getProp()->getInput(browser_));
			browser_->addProperty(e->getProp()->getOutput(browser_));
			browser_->addProperty(e->getProp()->getMisc(browser_));
		}
	}
}



QSize shelllet::creator::properties_component::sizeHint() const
{
	QSize size = __super::sizeHint();
	size.setWidth(size.width() * 0.7);
	return size;
}
