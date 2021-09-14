#include "common.hpp"
#include "model/activities_dom_item.h"
#include "common/private/object_p.h"
#include "model/private/elementdomitem_p.h"

shelllet::model::ActivitiesDomItem::ActivitiesDomItem(const XmlNode& node, int row, int depth, ActivitiesDomItem* parent)
	: Object(*new ActivitiesDomItemPrivate, nullptr)
{
	Q_D(ActivitiesDomItem);
	d->domNode = node;
	d->parentItem = parent;
	d->rowNumber = row;
	d->depth = depth;
}

shelllet::model::ActivitiesDomItem::~ActivitiesDomItem()
{
	Q_D(ActivitiesDomItem);
	qDeleteAll(d->childItems);
}

XmlNode shelllet::model::ActivitiesDomItem::node() const
{
	Q_D(const ActivitiesDomItem);
	return d->domNode;
}

shelllet::model::ActivitiesDomItem* shelllet::model::ActivitiesDomItem::parent()
{
	Q_D(ActivitiesDomItem);
	return d->parentItem;
}

shelllet::model::ActivitiesDomItem* shelllet::model::ActivitiesDomItem::child(int i)
{
	Q_D(ActivitiesDomItem);

	ActivitiesDomItem* childItem = d->childItems.value(i);
	if (childItem)
		return childItem;

	// if child does not yet exist, create it
	auto children = d->domNode.children();

	if (d->depth <= Environment::getInstance()->getOptions()->depth) {
		auto vi = children.begin();
		std::advance(vi, i);

		if (vi->type() == XmlNodeType::Element && vi != children.end()) {
			if (i >= 0) {
				
				childItem = new ActivitiesDomItem(*vi, i, d->depth + 1, this);
				d->childItems[i] = childItem;
			}
		}
	}

	return childItem;
}

int shelllet::model::ActivitiesDomItem::row() const
{
	Q_D(const ActivitiesDomItem);
	return d->rowNumber;
}