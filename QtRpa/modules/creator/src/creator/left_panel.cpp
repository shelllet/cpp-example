#include "common.hpp"
#include <qboxlayout.h>
#include "left_panel.h"

#include "files_info_component.h"
#include "packages_info_component.h"

#include "activities_search_widget.h"
#include "private/qwidget_p.h"

namespace shelllet {
	namespace creator {
		class LeftPanelPrivate : public QWidgetPrivate {
		public:
			QToolBox* toolBox =nullptr;

		};
	}
}
shelllet::creator::LeftPanel::LeftPanel(QWidget* parent)
	: QWidget(*new LeftPanelPrivate, parent, {})

{
	Q_D(LeftPanel);
	d->toolBox = new QToolBox(this);
	setLayout(new QVBoxLayout());
	layout()->setContentsMargins({ 0, 0, 0,0 });

	layout()->addWidget(d->toolBox);
	d->toolBox->setContentsMargins(0, 0, 0, 0);
	
}

shelllet::creator::LeftPanel::~LeftPanel()
{
}

void shelllet::creator::LeftPanel::create()
{
}

void shelllet::creator::LeftPanel::save(const Path& filename)
{
}

void shelllet::creator::LeftPanel::load(const Path& filename)
{
	Q_D(LeftPanel);
	for (auto i = 0; i < d->toolBox->count(); ++i) {
		d->toolBox->removeItem(i);
	}

	d->toolBox->addItem(new FilesInfoComponent,*filename.fileName().toQString());
	d->toolBox->addItem(new ActivitiesSearchWidget, tr("ToolBox"));

	for (auto i = 0; i < d->toolBox->count(); ++i) {
		auto* w = dynamic_cast<common::Serialization*>(d->toolBox->widget(i));
		if (w)
			w->load(filename);
	}
}

QSize shelllet::creator::LeftPanel::sizeHint() const
{
	QSize size = __super::sizeHint();
	size.setWidth(size.width() * 0.7);
	return size;
}
