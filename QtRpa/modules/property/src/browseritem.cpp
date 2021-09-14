#include "property/framework.h"
#include "qwidget.h"
#include "property/propertysheet.h"
#include "property/qtpropertybrowser.h"
#include "property/abstractpropertybrowser.h"
#include "property/browseritem.h"
#include "property/private/browseritem_p.h"

namespace shelllet{
    namespace property{
        
    }
}
using namespace shelllet::property;

BrowserItem::BrowserItem(BrowserItemPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}


void BrowserItemPrivate::addChild(BrowserItem* index, BrowserItem* after)
{
	if (m_children.contains(index))
		return;
	int idx = m_children.indexOf(after) + 1; // we insert after returned idx, if it was -1 then we set idx to 0;
	m_children.insert(idx, index);
}

void BrowserItemPrivate::removeChild(BrowserItem* index)
{
	m_children.removeAll(index);
}

/*!
	\class BrowserItem
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The BrowserItem class represents a property in
	a property browser instance.

	Browser items are created whenever a PropertySheet is inserted to the
	property browser. A BrowserItem uniquely identifies a
	browser's item. Thus, if the same PropertySheet is inserted multiple
	times, each occurrence gets its own unique BrowserItem. The
	items are owned by AbstractPropertyBrowser and automatically
	deleted when they are removed from the browser.

	You can traverse a browser's properties by calling parent() and
	children(). The property and the browser associated with an item
	are available as property() and browser().

	\sa AbstractPropertyBrowser, PropertySheet
*/

/*!
	Returns the property which is accosiated with this item. Note that
	several items can be associated with the same property instance in
	the same property browser.

	\sa AbstractPropertyBrowser::items()
*/

PropertySheet* BrowserItem::property() const
{
	Q_D(const BrowserItem);
	return d->m_property;
}

/*!
	Returns the parent item of \e this item. Returns 0 if \e this item
	is associated with top-level property in item's property browser.

	\sa children()
*/

BrowserItem* BrowserItem::parent() const
{
	Q_D(const BrowserItem);
	return d->m_parent;
}

/*!
	Returns the children items of \e this item. The properties
	reproduced from children items are always the same as
	reproduced from associated property' children, for example:

	\snippet doc/src/snippets/code/tools_shared_qtpropertybrowser_qtpropertybrowser.cpp 1

	The \e childrenItems list represents the same list as \e childrenProperties.
*/

QList<BrowserItem*> BrowserItem::children() const
{
	Q_D(const BrowserItem);
	return d->m_children;
}

/*!
	Returns the property browser which owns \e this item.
*/

AbstractPropertyBrowser* BrowserItem::browser() const
{
	Q_D(const BrowserItem);
	return d->m_browser;
}

BrowserItem::BrowserItem(AbstractPropertyBrowser* browser, PropertySheet* property, BrowserItem* parent)
	: BrowserItem(*new BrowserItemPrivate(browser, property, parent))
{
	d_ptr->q_ptr = this;
}

BrowserItem::~BrowserItem()
{
}