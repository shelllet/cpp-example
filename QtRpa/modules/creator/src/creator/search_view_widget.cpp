#include "common.hpp"
#include "creator.hpp"
#include <QHeaderView>
#include <qdir.h>
#include <qcoreapplication.h>
#include "search_view_widget.h"
#include "model.hpp"

namespace shelllet {
	static const  char* DISPLAY_XML_ATTRIBUTE_NAME = "display";
}

shelllet::creator::ActivitiesSearchViewWidget::ActivitiesSearchViewWidget(QWidget* parent /*= nullptr*/)
	: QTreeView(parent)
{
	/*std::filesystem::path p = Environment::getInstance()->getOptions()->assets;
	LOG_DEBUG("rpa") << "# working dir: " << std::filesystem::current_path() << std::endl;

	p /= "activities/activities.xml";*/

	ActivitiesManager::getInstance()->loadAll();

	setDragEnabled(true);
	setSelectionMode(QAbstractItemView::SingleSelection);
	setDragDropMode(QAbstractItemView::DragOnly);

	setModel(new model::ActivitiesDomModel(ActivitiesManager::getInstance()->document(), this));


	header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

shelllet::creator::ActivitiesSearchViewWidget::~ActivitiesSearchViewWidget()
{
}