#include <QVBoxLayout>
#include "packages_info_component.h"
using namespace shelllet::creator;
PackagesInfoComponent::PackagesInfoComponent(QWidget* parent)
	: QWidget(parent)
	, treeWidget(new QTreeWidget)
{
	setLayout(new QVBoxLayout);
	layout()->setContentsMargins({ 0, 0, 0,0 });

	layout()->addWidget(treeWidget);
}

PackagesInfoComponent::~PackagesInfoComponent()
{
}