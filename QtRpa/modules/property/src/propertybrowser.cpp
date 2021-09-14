#include "common.hpp"
#include "qwidget.h"
#include "qtreewidget.h"
#include "qlayout.h"
#include "qheaderview.h"
#include "qitemdelegate.h"
#include "property/propertysheet.h"
#include "property/qtpropertybrowser.h"
#include "property/abstractpropertybrowser.h"
#include "property/qtpropertybrowser.h"
#include "property/propertybrowser.h"
#include "property/propertyeditordelegate.h"
#include "property/browseritem.h"
#include "property/propertyeditorview.h"
#include "private/qwidget_p.h"
#include "property/private/abstractpropertybrowser_p.h"
#include "property/private/propertybrowser_p.h"
#include "qstyle.h"
#include "qcoreapplication.h"
#include "qstyleoption.h"
namespace shelllet {
	namespace property {

	}
}

using namespace shelllet::property;

PropertyBrowser::PropertyBrowser(QWidget* parentWidget, Object* parent /*= nullptr*/)
    :PropertyBrowser(*new PropertyBrowserPrivate, parentWidget)
{

}
PropertyBrowser::PropertyBrowser(PropertyBrowserPrivate& d, QWidget* parentWidget, Object* parent /*= nullptr*/)
	: AbstractPropertyBrowser(d, parentWidget)
{
	d.init(this);
	connect(this, SIGNAL(currentItemChanged(BrowserItem*)), this, SLOT(slotCurrentBrowserItemChanged(BrowserItem*)));
}



//  -------- PropertyBrowserPrivate implementation
PropertyBrowserPrivate::PropertyBrowserPrivate() :
	m_treeWidget(0),
	m_headerVisible(true),
	m_resizeMode(PropertyBrowser::Stretch),
	m_delegate(0),
	m_markPropertiesWithoutValue(false),
	m_browserChangedBlocked(false)
{
}

// Draw an icon indicating opened/closing branches
static QIcon drawIndicatorIcon(const QPalette& palette, QStyle* style)
{
	QPixmap pix(14, 14);
	pix.fill(Qt::transparent);
	QStyleOption branchOption;
	branchOption.rect = QRect(2, 2, 9, 9); // ### hardcoded in qcommonstyle.cpp
	branchOption.palette = palette;
	branchOption.state = QStyle::State_Children;

	QPainter p;
	// Draw closed state
	p.begin(&pix);
	style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
	p.end();
	QIcon rc = pix;
	rc.addPixmap(pix, QIcon::Selected, QIcon::Off);
	// Draw opened state
	branchOption.state |= QStyle::State_Open;
	pix.fill(Qt::transparent);
	p.begin(&pix);
	style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
	p.end();

	rc.addPixmap(pix, QIcon::Normal, QIcon::On);
	rc.addPixmap(pix, QIcon::Selected, QIcon::On);
	return rc;
}

void PropertyBrowserPrivate::init(QWidget* parent)
{
	Q_Q(PropertyBrowser);
	QHBoxLayout* layout = new QHBoxLayout(parent);
	layout->setContentsMargins(QMargins());
	m_treeWidget = new PropertyEditorView(parent);
	m_treeWidget->setEditorPrivate(this);
	m_treeWidget->setIconSize(QSize(18, 18));
	layout->addWidget(m_treeWidget);

	m_treeWidget->setColumnCount(2);
	QStringList labels;
	labels.append(QCoreApplication::translate("PropertyBrowser", "Property"));
	labels.append(QCoreApplication::translate("PropertyBrowser", "Value"));
	m_treeWidget->setHeaderLabels(labels);
	m_treeWidget->setAlternatingRowColors(true);
	m_treeWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);
	m_delegate = new PropertyEditorDelegate(parent);
	m_delegate->setEditorPrivate(this);
	m_treeWidget->setItemDelegate(m_delegate);
	m_treeWidget->header()->setSectionsMovable(false);
	m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

	m_expandIcon = drawIndicatorIcon(q->palette(), q->style());

	QObject::connect(m_treeWidget, SIGNAL(collapsed(QModelIndex)), q, SLOT(slotCollapsed(QModelIndex)));
	QObject::connect(m_treeWidget, SIGNAL(expanded(QModelIndex)), q, SLOT(slotExpanded(QModelIndex)));
	QObject::connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), q, SLOT(slotCurrentTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
}

BrowserItem* PropertyBrowserPrivate::currentItem() const
{
	if (QTreeWidgetItem* treeItem = m_treeWidget->currentItem())
		return m_itemToIndex.value(treeItem);
	return 0;
}

void PropertyBrowserPrivate::setCurrentItem(BrowserItem* browserItem, bool block)
{
	const bool blocked = block ? m_treeWidget->blockSignals(true) : false;
	if (browserItem == 0)
		m_treeWidget->setCurrentItem(0);
	else
		m_treeWidget->setCurrentItem(m_indexToItem.value(browserItem));
	if (block)
		m_treeWidget->blockSignals(blocked);
}

PropertySheet* PropertyBrowserPrivate::indexToProperty(const QModelIndex& index) const
{
	QTreeWidgetItem* item = m_treeWidget->indexToItem(index);
	BrowserItem* idx = m_itemToIndex.value(item);
	if (idx)
		return idx->property();
	return 0;
}

BrowserItem* PropertyBrowserPrivate::indexToBrowserItem(const QModelIndex& index) const
{
	QTreeWidgetItem* item = m_treeWidget->indexToItem(index);
	return m_itemToIndex.value(item);
}

QTreeWidgetItem* PropertyBrowserPrivate::indexToItem(const QModelIndex& index) const
{
	return m_treeWidget->indexToItem(index);
}

bool PropertyBrowserPrivate::lastColumn(int column) const
{
	return m_treeWidget->header()->visualIndex(column) == m_treeWidget->columnCount() - 1;
}

void PropertyBrowserPrivate::disableItem(QTreeWidgetItem* item) const
{
	Qt::ItemFlags flags = item->flags();
	if (flags & Qt::ItemIsEnabled) {
		flags &= ~Qt::ItemIsEnabled;
		item->setFlags(flags);
		m_delegate->closeEditor(m_itemToIndex[item]->property());
		const int childCount = item->childCount();
		for (int i = 0; i < childCount; i++) {
			QTreeWidgetItem* child = item->child(i);
			disableItem(child);
		}
	}
}

void PropertyBrowserPrivate::enableItem(QTreeWidgetItem* item) const
{
	Qt::ItemFlags flags = item->flags();
	flags |= Qt::ItemIsEnabled;
	item->setFlags(flags);
	const int childCount = item->childCount();
	for (int i = 0; i < childCount; i++) {
		QTreeWidgetItem* child = item->child(i);
		PropertySheet* property = m_itemToIndex[child]->property();
		if (property->isEnabled()) {
			enableItem(child);
		}
	}
}

bool PropertyBrowserPrivate::hasValue(QTreeWidgetItem* item) const
{
	BrowserItem* browserItem = m_itemToIndex.value(item);
	if (browserItem)
		return browserItem->property()->hasValue();
	return false;
}

void PropertyBrowserPrivate::propertyInserted(BrowserItem* index, BrowserItem* afterIndex)
{
	QTreeWidgetItem* afterItem = m_indexToItem.value(afterIndex);
	QTreeWidgetItem* parentItem = m_indexToItem.value(index->parent());

	QTreeWidgetItem* newItem = 0;
	if (parentItem) {
		newItem = new QTreeWidgetItem(parentItem, afterItem);
	}
	else {
		newItem = new QTreeWidgetItem(m_treeWidget, afterItem);
	}
	m_itemToIndex[newItem] = index;
	m_indexToItem[index] = newItem;

	newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
	newItem->setExpanded(true);

	updateItem(newItem);
}

void PropertyBrowserPrivate::propertyRemoved(BrowserItem* index)
{
	QTreeWidgetItem* item = m_indexToItem.value(index);

	if (m_treeWidget->currentItem() == item) {
		m_treeWidget->setCurrentItem(0);
	}

	delete item;

	m_indexToItem.remove(index);
	m_itemToIndex.remove(item);
	m_indexToBackgroundColor.remove(index);
}

void PropertyBrowserPrivate::propertyChanged(BrowserItem* index)
{
	QTreeWidgetItem* item = m_indexToItem.value(index);

	updateItem(item);
}

void PropertyBrowserPrivate::updateItem(QTreeWidgetItem* item)
{
	PropertySheet* property = m_itemToIndex[item]->property();
	QIcon expandIcon;
	if (property->hasValue()) {
		const QString valueToolTip = property->valueToolTip();
		const String valueText = property->valueText();
		item->setToolTip(1, valueToolTip.isEmpty() ? *valueText.toQString() : valueToolTip);
		item->setIcon(1, property->valueIcon());
		item->setText(1, *valueText.toQString());
	}
	else if (markPropertiesWithoutValue() && !m_treeWidget->rootIsDecorated()) {
		expandIcon = m_expandIcon;
	}
	item->setIcon(0, expandIcon);
	item->setFirstColumnSpanned(!property->hasValue());
	const QString descriptionToolTip = property->descriptionToolTip();
	const QString propertyName = property->propertyName();
	item->setToolTip(0, descriptionToolTip.isEmpty() ? propertyName : descriptionToolTip);
	item->setStatusTip(0, property->statusTip());
	item->setWhatsThis(0, property->whatsThis());
	item->setText(0, propertyName);
	bool wasEnabled = item->flags() & Qt::ItemIsEnabled;
	bool isEnabled = wasEnabled;
	if (property->isEnabled()) {
		QTreeWidgetItem* parent = item->parent();
		if (!parent || (parent->flags() & Qt::ItemIsEnabled))
			isEnabled = true;
		else
			isEnabled = false;
	}
	else {
		isEnabled = false;
	}
	if (wasEnabled != isEnabled) {
		if (isEnabled)
			enableItem(item);
		else
			disableItem(item);
	}
	m_treeWidget->viewport()->update();
}

QColor PropertyBrowserPrivate::calculatedBackgroundColor(BrowserItem* item) const
{
	BrowserItem* i = item;
	const QMap<BrowserItem*, QColor>::const_iterator itEnd = m_indexToBackgroundColor.constEnd();
	while (i) {
		QMap<BrowserItem*, QColor>::const_iterator it = m_indexToBackgroundColor.constFind(i);
		if (it != itEnd)
			return it.value();
		i = i->parent();
	}
	return QColor();
}

void PropertyBrowserPrivate::slotCollapsed(const QModelIndex& index)
{
	Q_Q(PropertyBrowser);
	QTreeWidgetItem* item = indexToItem(index);
	BrowserItem* idx = m_itemToIndex.value(item);
	if (item)
		emit q->collapsed(idx);
}

void PropertyBrowserPrivate::slotExpanded(const QModelIndex& index)
{
	Q_Q(PropertyBrowser);
	QTreeWidgetItem* item = indexToItem(index);
	BrowserItem* idx = m_itemToIndex.value(item);
	if (item)
		emit q->expanded(idx);
}

void PropertyBrowserPrivate::slotCurrentBrowserItemChanged(BrowserItem* item)
{
	if (!m_browserChangedBlocked && item != currentItem())
		setCurrentItem(item, true);
}

void PropertyBrowserPrivate::slotCurrentTreeItemChanged(QTreeWidgetItem* newItem, QTreeWidgetItem*)
{
	Q_Q(PropertyBrowser);
	BrowserItem* browserItem = newItem ? m_itemToIndex.value(newItem) : 0;
	m_browserChangedBlocked = true;
	q->setCurrentItem(browserItem);
	m_browserChangedBlocked = false;
}

QTreeWidgetItem* PropertyBrowserPrivate::editedItem() const
{
	return m_delegate->editedItem();
}

void PropertyBrowserPrivate::editItem(BrowserItem* browserItem)
{
	if (QTreeWidgetItem* treeItem = m_indexToItem.value(browserItem, 0)) {
		m_treeWidget->setCurrentItem(treeItem, 1);
		m_treeWidget->editItem(treeItem, 1);
	}
}

/*!
	\class PropertyBrowser
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The PropertyBrowser class provides QTreeWidget based
	property browser.

	A property browser is a widget that enables the user to edit a
	given set of properties. Each property is represented by a label
	specifying the property's name, and an editing widget (e.g. a line
	edit or a combobox) holding its value. A property can have zero or
	more subproperties.

	PropertyBrowser provides a tree based view for all nested
	properties, i.e. properties that have subproperties can be in an
	expanded (subproperties are visible) or collapsed (subproperties
	are hidden) state. For example:

	\image qttreepropertybrowser.png

	Use the QtAbstractPropertyBrowser API to add, insert and remove
	properties from an instance of the PropertyBrowser class.
	The properties themselves are created and managed by
	implementations of the QtAbstractPropertyManager class.

	\sa QtGroupBoxPropertyBrowser, QtAbstractPropertyBrowser
*/

/*!
	\fn void PropertyBrowser::collapsed(BrowserItem *item)

	This signal is emitted when the \a item is collapsed.

	\sa expanded(), setExpanded()
*/

/*!
	\fn void PropertyBrowser::expanded(BrowserItem *item)

	This signal is emitted when the \a item is expanded.

	\sa collapsed(), setExpanded()
*/

/*!
	Creates a property browser with the given \a parent.
*/

/*!
	Destroys this property browser.

	Note that the properties that were inserted into this browser are
	\e not destroyed since they may still be used in other
	browsers. The properties are owned by the manager that created
	them.

	\sa PropertySheet, QtAbstractPropertyManager
*/
PropertyBrowser::~PropertyBrowser()
{
}

/*!
	\property PropertyBrowser::indentation
	\brief indentation of the items in the tree view.
*/
int PropertyBrowser::indentation() const
{
	Q_D(const PropertyBrowser);
	return d->m_treeWidget->indentation();
}

void PropertyBrowser::setIndentation(int i)
{
	Q_D(PropertyBrowser);
	d->m_treeWidget->setIndentation(i);
}

/*!
  \property PropertyBrowser::rootIsDecorated
  \brief whether to show controls for expanding and collapsing root items.
*/
bool PropertyBrowser::rootIsDecorated() const
{
	Q_D(const PropertyBrowser);
	return d->m_treeWidget->rootIsDecorated();
}

void PropertyBrowser::setRootIsDecorated(bool show)
{
	Q_D(PropertyBrowser);
	d->m_treeWidget->setRootIsDecorated(show);
	for (auto it = d->m_itemToIndex.cbegin(), end = d->m_itemToIndex.cend(); it != end; ++it) {
		PropertySheet* property = it.value()->property();
		if (!property->hasValue())
			d->updateItem(it.key());
	}
}

/*!
  \property PropertyBrowser::alternatingRowColors
  \brief whether to draw the background using alternating colors.
  By default this property is set to true.
*/
bool PropertyBrowser::alternatingRowColors() const
{
	Q_D(const PropertyBrowser);
	return d->m_treeWidget->alternatingRowColors();
}

void PropertyBrowser::setAlternatingRowColors(bool enable)
{
	Q_D(const PropertyBrowser);
	d->m_treeWidget->setAlternatingRowColors(enable);
}

/*!
  \property PropertyBrowser::headerVisible
  \brief whether to show the header.
*/
bool PropertyBrowser::isHeaderVisible() const
{
	Q_D(const PropertyBrowser);
	return d->m_headerVisible;
}

void PropertyBrowser::setHeaderVisible(bool visible)
{
	Q_D(PropertyBrowser);
	if (d->m_headerVisible == visible)
		return;

	d->m_headerVisible = visible;
	d->m_treeWidget->header()->setVisible(visible);
}

/*!
  \enum PropertyBrowser::ResizeMode

  The resize mode specifies the behavior of the header sections.

  \value Interactive The user can resize the sections.
  The sections can also be resized programmatically using setSplitterPosition().

  \value Fixed The user cannot resize the section.
  The section can only be resized programmatically using setSplitterPosition().

  \value Stretch QHeaderView will automatically resize the section to fill the available space.
  The size cannot be changed by the user or programmatically.

  \value ResizeToContents QHeaderView will automatically resize the section to its optimal
  size based on the contents of the entire column.
  The size cannot be changed by the user or programmatically.

  \sa setResizeMode()
*/

/*!
	\property PropertyBrowser::resizeMode
	\brief the resize mode of setions in the header.
*/

PropertyBrowser::ResizeMode PropertyBrowser::resizeMode() const
{
	Q_D(const PropertyBrowser);
	return d->m_resizeMode;
}

void PropertyBrowser::setResizeMode(PropertyBrowser::ResizeMode mode)
{
	Q_D(PropertyBrowser);
	if (d->m_resizeMode == mode)
		return;

	d->m_resizeMode = mode;
	QHeaderView::ResizeMode m = QHeaderView::Stretch;
	switch (mode) {
	case PropertyBrowser::Interactive:      m = QHeaderView::Interactive;      break;
	case PropertyBrowser::Fixed:            m = QHeaderView::Fixed;            break;
	case PropertyBrowser::ResizeToContents: m = QHeaderView::ResizeToContents; break;
	case PropertyBrowser::Stretch:
	default:                                      m = QHeaderView::Stretch;          break;
	}
	d->m_treeWidget->header()->setSectionResizeMode(m);
}

/*!
	\property PropertyBrowser::splitterPosition
	\brief the position of the splitter between the colunms.
*/

int PropertyBrowser::splitterPosition() const
{
	Q_D(const PropertyBrowser);
	return d->m_treeWidget->header()->sectionSize(0);
}

void PropertyBrowser::setSplitterPosition(int position)
{
	Q_D( PropertyBrowser);
	d->m_treeWidget->header()->resizeSection(0, position);
}

/*!
	Sets the \a item to either collapse or expanded, depending on the value of \a expanded.

	\sa isExpanded(), expanded(), collapsed()
*/

void PropertyBrowser::setExpanded(BrowserItem* item, bool expanded)
{
	Q_D(PropertyBrowser);
	QTreeWidgetItem* treeItem = d->m_indexToItem.value(item);
	if (treeItem)
		treeItem->setExpanded(expanded);
}

/*!
	Returns true if the \a item is expanded; otherwise returns false.

	\sa setExpanded()
*/

bool PropertyBrowser::isExpanded(BrowserItem* item) const
{
	Q_D(const PropertyBrowser);
	QTreeWidgetItem* treeItem = d->m_indexToItem.value(item);
	if (treeItem)
		return treeItem->isExpanded();
	return false;
}

/*!
	Returns true if the \a item is visible; otherwise returns false.

	\sa setItemVisible()
	\since 4.5
*/

bool PropertyBrowser::isItemVisible(BrowserItem* item) const
{
	Q_D(const PropertyBrowser);
	if (const QTreeWidgetItem* treeItem = d->m_indexToItem.value(item))
		return !treeItem->isHidden();
	return false;
}

/*!
	Sets the \a item to be visible, depending on the value of \a visible.

   \sa isItemVisible()
   \since 4.5
*/

void PropertyBrowser::setItemVisible(BrowserItem* item, bool visible)
{
	Q_D(const PropertyBrowser);
	if (QTreeWidgetItem* treeItem = d->m_indexToItem.value(item))
		treeItem->setHidden(!visible);
}

/*!
	Sets the \a item's background color to \a color. Note that while item's background
	is rendered every second row is being drawn with alternate color (which is a bit lighter than items \a color)

	\sa backgroundColor(), calculatedBackgroundColor()
*/

void PropertyBrowser::setBackgroundColor(BrowserItem* item, const QColor& color)
{
	Q_D(PropertyBrowser);
	if (!d->m_indexToItem.contains(item))
		return;
	if (color.isValid())
		d->m_indexToBackgroundColor[item] = color;
	else
		d->m_indexToBackgroundColor.remove(item);
	d->m_treeWidget->viewport()->update();
}

/*!
	Returns the \a item's color. If there is no color set for item it returns invalid color.

	\sa calculatedBackgroundColor(), setBackgroundColor()
*/

QColor PropertyBrowser::backgroundColor(BrowserItem* item) const
{
	Q_D(const PropertyBrowser);
	return d->m_indexToBackgroundColor.value(item);
}

/*!
	Returns the \a item's color. If there is no color set for item it returns parent \a item's
	color (if there is no color set for parent it returns grandparent's color and so on). In case
	the color is not set for \a item and it's top level item it returns invalid color.

	\sa backgroundColor(), setBackgroundColor()
*/

QColor PropertyBrowser::calculatedBackgroundColor(BrowserItem* item) const
{
	Q_D(const PropertyBrowser);
	return d->calculatedBackgroundColor(item);
}

/*!
	\property PropertyBrowser::propertiesWithoutValueMarked
	\brief whether to enable or disable marking properties without value.

	When marking is enabled the item's background is rendered in dark color and item's
	foreground is rendered with light color.

	\sa propertiesWithoutValueMarked()
*/
void PropertyBrowser::setPropertiesWithoutValueMarked(bool mark)
{
	Q_D(PropertyBrowser);
	if (d->m_markPropertiesWithoutValue == mark)
		return;

	d->m_markPropertiesWithoutValue = mark;
	for (auto it = d->m_itemToIndex.cbegin(), end = d->m_itemToIndex.cend(); it != end; ++it) {
		PropertySheet* property = it.value()->property();
		if (!property->hasValue())
			d->updateItem(it.key());
	}
	d->m_treeWidget->viewport()->update();
}

bool PropertyBrowser::propertiesWithoutValueMarked() const
{
	Q_D(const PropertyBrowser);
	return d->m_markPropertiesWithoutValue;
}

/*!
	\reimp
*/
void PropertyBrowser::itemInserted(BrowserItem* item, BrowserItem* afterItem)
{
	Q_D(PropertyBrowser);
	d->propertyInserted(item, afterItem);
}

/*!
	\reimp
*/
void PropertyBrowser::itemRemoved(BrowserItem* item)
{
	Q_D(PropertyBrowser);
	d->propertyRemoved(item);
}

/*!
	\reimp
*/
void PropertyBrowser::itemChanged(BrowserItem* item)
{
	Q_D(PropertyBrowser);
	d->propertyChanged(item);
}

/*!
	Sets the current item to \a item and opens the relevant editor for it.
*/
void PropertyBrowser::editItem(BrowserItem* item)
{
	Q_D(PropertyBrowser);
	d->editItem(item);
}
