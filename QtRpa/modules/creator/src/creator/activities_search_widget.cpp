#include "common.hpp"
#include <QCoreApplication>
#include <QVBoxLayout>
#include "activities_search_widget.h"
#include "model/activities_dom_item.h"
#include "events/activity_create_event.h"
#include "events/common_event.h"
#include "private/qwidget_p.h"

using namespace shelllet::creator;
namespace shelllet {
	namespace creator {
		class ActivitiesSearchWidgetPrivate : public QWidgetPrivate {
		public:
			ActivitiesSearchInputWidget* lineEdit = nullptr;
			ActivitiesSearchViewWidget* treeView = nullptr;

			void setupUi(ActivitiesSearchWidget *self) {
				lineEdit = new ActivitiesSearchInputWidget(self);
				treeView = new ActivitiesSearchViewWidget(self);

				self->setLayout(new QVBoxLayout);

				self->layout()->addWidget(lineEdit);
				self->layout()->addWidget(treeView);
				self->layout()->setContentsMargins(1, 1, 1, 1);
			}
		};
	}
}
ActivitiesSearchWidget::ActivitiesSearchWidget(QWidget* parent)
	: QWidget(*new ActivitiesSearchWidgetPrivate, parent, {})

{
	Q_D(ActivitiesSearchWidget);
	d->setupUi(this);
	connect(d->treeView, &QAbstractItemView::doubleClicked, this, &ActivitiesSearchWidget::itemDoubleClicked);
}

ActivitiesSearchWidget::~ActivitiesSearchWidget()
{
}

void ActivitiesSearchWidget::itemDoubleClicked(const QModelIndex& index)
{
	const auto* item = static_cast<model::ActivitiesDomItem*>(index.internalPointer());
	auto meta = item->node().attribute("meta").value();
	QCoreApplication::postEvent(events::EventDispatcher::Dispatcher(), new events::ActivityCreateEvent(meta));
}