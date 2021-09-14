#include "property/framework.h"
#include "qwidget.h"
#include "qtreewidget.h"
#include "property/propertysheet.h"
#include "property/qtpropertybrowser.h"
#include "property/browseritem.h"
#include "property/abstracteditorfactorybase.h"
#include "property/abstracteditorfactory.h"
#include "property/abstractpropertymanager.h"
#include "property/abstractpropertybrowser.h"
#include "private/qwidget_p.h"
#include "property/private/browseritem_p.h"
#include "property/private/abstractpropertybrowser_p.h"

namespace shelllet {
	namespace property {
	}
}
using namespace shelllet::property;


AbstractPropertyBrowser::AbstractPropertyBrowser(AbstractPropertyBrowserPrivate& d, QWidget* parent /*= nullptr*/)
	: QWidget(d, parent, Qt::WindowFlags())
{

}




////////////////////////////////////

typedef QMap<AbstractPropertyBrowser*, QMap<AbstractPropertyManager*,
	AbstractEditorFactoryBase*> > Map1;
typedef QMap<AbstractPropertyManager*, QMap<AbstractEditorFactoryBase*,
	QList<AbstractPropertyBrowser*> > > Map2;
Q_GLOBAL_STATIC(Map1, m_viewToManagerToFactory)
Q_GLOBAL_STATIC(Map2, m_managerToFactoryToViews)

AbstractPropertyBrowserPrivate::AbstractPropertyBrowserPrivate() :
	m_currentItem(0)
{
}

void AbstractPropertyBrowserPrivate::insertSubTree(PropertySheet* property,
	PropertySheet* parentProperty)
{
	Q_Q(AbstractPropertyBrowser);
	if (m_propertyToParents.contains(property)) {
		// property was already inserted, so its manager is connected
		// and all its children are inserted and theirs managers are connected
		// we just register new parent (parent has to be new).
		m_propertyToParents[property].append(parentProperty);
		// don't need to update m_managerToProperties map since
		// m_managerToProperties[manager] already contains property.
		return;
	}
	AbstractPropertyManager* manager = property->propertyManager();
	if (m_managerToProperties[manager].isEmpty()) {
		// connect manager's signals
		connect(manager, &AbstractPropertyManager::propertyInserted, this, &AbstractPropertyBrowserPrivate::slotPropertyInserted);
		connect(manager, &AbstractPropertyManager::propertyRemoved, this, &AbstractPropertyBrowserPrivate::slotPropertyRemoved);
		connect(manager, &AbstractPropertyManager::propertyDestroyed, this, &AbstractPropertyBrowserPrivate::slotPropertyDestroyed);
		connect(manager, &AbstractPropertyManager::propertyChanged,	this, &AbstractPropertyBrowserPrivate::slotPropertyDataChanged);
	}
	m_managerToProperties[manager].append(property);
	m_propertyToParents[property].append(parentProperty);

	const QList<PropertySheet*> subList = property->subProperties();
	for (PropertySheet* subProperty : subList)
		insertSubTree(subProperty, property);
}

void AbstractPropertyBrowserPrivate::removeSubTree(PropertySheet* property,
	PropertySheet* parentProperty)
{
	Q_Q(AbstractPropertyBrowser);
	if (!m_propertyToParents.contains(property)) {
		// ASSERT
		return;
	}

	m_propertyToParents[property].removeAll(parentProperty);
	if (!m_propertyToParents[property].isEmpty())
		return;

	m_propertyToParents.remove(property);
	AbstractPropertyManager* manager = property->propertyManager();
	m_managerToProperties[manager].removeAll(property);
	if (m_managerToProperties[manager].isEmpty()) {
		// disconnect manager's signals
		disconnect(manager, &AbstractPropertyManager::propertyInserted, this, &AbstractPropertyBrowserPrivate::slotPropertyInserted);
		disconnect(manager, &AbstractPropertyManager::propertyRemoved, this, &AbstractPropertyBrowserPrivate::slotPropertyRemoved);
		disconnect(manager, &AbstractPropertyManager::propertyDestroyed, this, &AbstractPropertyBrowserPrivate::slotPropertyDestroyed);
		disconnect(manager, &AbstractPropertyManager::propertyChanged, this, &AbstractPropertyBrowserPrivate::slotPropertyDataChanged);

		m_managerToProperties.remove(manager);
	}

	const QList<PropertySheet*> subList = property->subProperties();
	for (PropertySheet* subProperty : subList)
		removeSubTree(subProperty, property);
}

void AbstractPropertyBrowserPrivate::createBrowserIndexes(PropertySheet* property, PropertySheet* parentProperty, PropertySheet* afterProperty)
{
	QMap<BrowserItem*, BrowserItem*> parentToAfter;
	if (afterProperty) {
		QMap<PropertySheet*, QList<BrowserItem*> >::ConstIterator it =
			m_propertyToIndexes.constFind(afterProperty);
		if (it == m_propertyToIndexes.constEnd())
			return;

		for (BrowserItem* idx : it.value()) {
			BrowserItem* parentIdx = idx->parent();
			if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
				parentToAfter[idx->parent()] = idx;
		}
	}
	else if (parentProperty) {
		QMap<PropertySheet*, QList<BrowserItem*> >::ConstIterator it =
			m_propertyToIndexes.find(parentProperty);
		if (it == m_propertyToIndexes.constEnd())
			return;

		for (BrowserItem* idx : it.value())
			parentToAfter[idx] = 0;
	}
	else {
		parentToAfter[0] = 0;
	}

	const QMap<BrowserItem*, BrowserItem*>::ConstIterator pcend = parentToAfter.constEnd();
	for (QMap<BrowserItem*, BrowserItem*>::ConstIterator it = parentToAfter.constBegin(); it != pcend; ++it)
		createBrowserIndex(property, it.key(), it.value());
}

BrowserItem* AbstractPropertyBrowserPrivate::createBrowserIndex(PropertySheet* property,
	BrowserItem* parentIndex, BrowserItem* afterIndex)
{
	Q_Q(AbstractPropertyBrowser);
	BrowserItem* newIndex = new BrowserItem(q, property, parentIndex);
	if (parentIndex) {
		parentIndex->d_func()->addChild(newIndex, afterIndex);
	}
	else {
		m_topLevelPropertyToIndex[property] = newIndex;
		m_topLevelIndexes.insert(m_topLevelIndexes.indexOf(afterIndex) + 1, newIndex);
	}
	m_propertyToIndexes[property].append(newIndex);

	q->itemInserted(newIndex, afterIndex);

	const QList<PropertySheet*> subItems = property->subProperties();
	BrowserItem* afterChild = 0;
	for (PropertySheet* child : subItems)
		afterChild = createBrowserIndex(child, newIndex, afterChild);
	return newIndex;
}

void AbstractPropertyBrowserPrivate::removeBrowserIndexes(PropertySheet* property, PropertySheet* parentProperty)
{
	QList<BrowserItem*> toRemove;
	QMap<PropertySheet*, QList<BrowserItem*> >::ConstIterator it =
		m_propertyToIndexes.constFind(property);
	if (it == m_propertyToIndexes.constEnd())
		return;

	for (BrowserItem* idx : it.value()) {
		BrowserItem* parentIdx = idx->parent();
		if ((parentProperty && parentIdx && parentIdx->property() == parentProperty) || (!parentProperty && !parentIdx))
			toRemove.append(idx);
	}

	for (BrowserItem* index : qAsConst(toRemove))
		removeBrowserIndex(index);
}

void AbstractPropertyBrowserPrivate::removeBrowserIndex(BrowserItem* index)
{
	Q_Q(AbstractPropertyBrowser);
	QList<BrowserItem*> children = index->children();
	for (int i = children.count(); i > 0; i--) {
		removeBrowserIndex(children.at(i - 1));
	}

	q->itemRemoved(index);

	if (index->parent()) {
		index->parent()->d_func()->removeChild(index);
	}
	else {
		m_topLevelPropertyToIndex.remove(index->property());
		m_topLevelIndexes.removeAll(index);
	}

	PropertySheet* property = index->property();

	m_propertyToIndexes[property].removeAll(index);
	if (m_propertyToIndexes[property].isEmpty())
		m_propertyToIndexes.remove(property);

	delete index;
}

void AbstractPropertyBrowserPrivate::clearIndex(BrowserItem* index)
{
	const QList<BrowserItem*> children = index->children();
	for (BrowserItem* item : children)
		clearIndex(item);
	delete index;
}

void AbstractPropertyBrowserPrivate::slotPropertyInserted(PropertySheet* property,
	PropertySheet* parentProperty, PropertySheet* afterProperty)
{
	if (!m_propertyToParents.contains(parentProperty))
		return;
	createBrowserIndexes(property, parentProperty, afterProperty);
	insertSubTree(property, parentProperty);
	//q_ptr->propertyInserted(property, parentProperty, afterProperty);
}

void AbstractPropertyBrowserPrivate::slotPropertyRemoved(PropertySheet* property,
	PropertySheet* parentProperty)
{
	if (!m_propertyToParents.contains(parentProperty))
		return;
	removeSubTree(property, parentProperty); // this line should be probably moved down after propertyRemoved call
	//q_ptr->propertyRemoved(property, parentProperty);
	removeBrowserIndexes(property, parentProperty);
}

void AbstractPropertyBrowserPrivate::slotPropertyDestroyed(PropertySheet* property)
{
	Q_Q(AbstractPropertyBrowser);
	if (!m_subItems.contains(property))
		return;
	q->removeProperty(property);
}

void AbstractPropertyBrowserPrivate::slotPropertyDataChanged(PropertySheet* property)
{
	Q_Q(AbstractPropertyBrowser);
	if (!m_propertyToParents.contains(property))
		return;

	QMap<PropertySheet*, QList<BrowserItem*> >::ConstIterator it =
		m_propertyToIndexes.find(property);
	if (it == m_propertyToIndexes.constEnd())
		return;

	const QList<BrowserItem*> indexes = it.value();
	for (BrowserItem* idx : indexes)
		q->itemChanged(idx);
	//q_ptr->propertyChanged(property);
}

/*!
	\class AbstractPropertyBrowser
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief AbstractPropertyBrowser provides a base class for
	implementing property browsers.

	A property browser is a widget that enables the user to edit a
	given set of properties.  Each property is represented by a label
	specifying the property's name, and an editing widget (e.g. a line
	edit or a combobox) holding its value. A property can have zero or
	more subproperties.

	\image qtpropertybrowser.png

	The top level properties can be retrieved using the
	properties() function. To traverse each property's
	subproperties, use the PropertySheet::subProperties() function. In
	addition, the set of top level properties can be manipulated using
	the addProperty(), insertProperty() and removeProperty()
	functions. Note that the PropertySheet class provides a corresponding
	set of functions making it possible to manipulate the set of
	subproperties as well.

	To remove all the properties from the property browser widget, use
	the clear() function. This function will clear the editor, but it
	will not delete the properties since they can still be used in
	other editors.

	The properties themselves are created and managed by
	implementations of the QtAbstractPropertyManager class. A manager
	can handle (i.e. create and manage) properties of a given type. In
	the property browser the managers are associated with
	implementations of the QtAbstractEditorFactory: A factory is a
	class able to create an editing widget of a specified type.

	When using a property browser widget, managers must be created for
	each of the required property types before the properties
	themselves can be created. To ensure that the properties' values
	will be displayed using suitable editing widgets, the managers
	must be associated with objects of the preferred factory
	implementations using the setFactoryForManager() function. The
	property browser will use these associations to determine which
	factory it should use to create the preferred editing widget.

	Note that a factory can be associated with many managers, but a
	manager can only be associated with one single factory within the
	context of a single property browser.  The associations between
	managers and factories can at any time be removed using the
	unsetFactoryForManager() function.

	Whenever the property data changes or a property is inserted or
	removed, the itemChanged(), itemInserted() or
	itemRemoved() functions are called, respectively. These
	functions must be reimplemented in derived classes in order to
	update the property browser widget. Be aware that some property
	instances can appear several times in an abstract tree
	structure. For example:

	\table 100%
	\row
	\li
	\snippet doc/src/snippets/code/tools_shared_qtpropertybrowser_qtpropertybrowser.cpp 2
	\li  \image qtpropertybrowser-duplicate.png
	\endtable

	The addProperty() function returns a BrowserItem that uniquely
	identifies the created item.

	To make a property editable in the property browser, the
	createEditor() function must be called to provide the
	property with a suitable editing widget.

	Note that there are two ready-made property browser
	implementations:

	\list
		\li QtGroupBoxPropertyBrowser
		\li QtTreePropertyBrowser
	\endlist

	\sa QtAbstractPropertyManager, QtAbstractEditorFactoryBase
*/

/*!
	\fn void AbstractPropertyBrowser::setFactoryForManager(PropertyManager *manager,
					QtAbstractEditorFactory<PropertyManager> *factory)

	Connects the given \a manager to the given \a factory, ensuring
	that properties of the \a manager's type will be displayed with an
	editing widget suitable for their value.

	For example:

	\snippet doc/src/snippets/code/tools_shared_qtpropertybrowser_qtpropertybrowser.cpp 3

	In this example the \c myInteger property's value is displayed
	with a QSpinBox widget, while the \c myDouble property's value is
	displayed with a QDoubleSpinBox widget.

	Note that a factory can be associated with many managers, but a
	manager can only be associated with one single factory.  If the
	given \a manager already is associated with another factory, the
	old association is broken before the new one established.

	This function ensures that the given \a manager and the given \a
	factory are compatible, and it automatically calls the
	QtAbstractEditorFactory::addPropertyManager() function if necessary.

	\sa unsetFactoryForManager()
*/

/*!
	\fn virtual void AbstractPropertyBrowser::itemInserted(BrowserItem *insertedItem,
		BrowserItem *precedingItem) = 0

	This function is called to update the widget whenever a property
	is inserted or added to the property browser, passing pointers to
	the \a insertedItem of property and the specified
	\a precedingItem as parameters.

	If \a precedingItem is 0, the \a insertedItem was put at
	the beginning of its parent item's list of subproperties. If
	the parent of \a insertedItem is 0, the \a insertedItem was added as a top
	level property of \e this property browser.

	This function must be reimplemented in derived classes. Note that
	if the \a insertedItem's property has subproperties, this
	method will be called for those properties as soon as the current call is finished.

	\sa insertProperty(), addProperty()
*/

/*!
	\fn virtual void AbstractPropertyBrowser::itemRemoved(BrowserItem *item) = 0

	This function is called to update the widget whenever a property
	is removed from the property browser, passing the pointer to the
	\a item of the property as parameters. The passed \a item is
	deleted just after this call is finished.

	If the the parent of \a item is 0, the removed \a item was a
	top level property in this editor.

	This function must be reimplemented in derived classes. Note that
	if the removed \a item's property has subproperties, this
	method will be called for those properties just before the current call is started.

	\sa removeProperty()
*/

/*!
	\fn virtual void AbstractPropertyBrowser::itemChanged(BrowserItem *item) = 0

	This function is called whenever a property's data changes,
	passing a pointer to the \a item of property as parameter.

	This function must be reimplemented in derived classes in order to
	update the property browser widget whenever a property's name,
	tool tip, status tip, "what's this" text, value text or value icon
	changes.

	Note that if the property browser contains several occurrences of
	the same property, this method will be called once for each
	occurrence (with a different item each time).

	\sa PropertySheet, items()
*/

/*!
	Creates an abstract property browser with the given \a parent.
*/
AbstractPropertyBrowser::AbstractPropertyBrowser(QWidget* parent)
	: AbstractPropertyBrowser(*new AbstractPropertyBrowserPrivate, parent)
{
}

/*!
	Destroys the property browser, and destroys all the items that were
	created by this property browser.

	Note that the properties that were displayed in the editor are not
	deleted since they still can be used in other editors. Neither
	does the destructor delete the property managers and editor
	factories that were used by this property browser widget unless
	this widget was their parent.

	\sa QtAbstractPropertyManager::~QtAbstractPropertyManager()
*/
AbstractPropertyBrowser::~AbstractPropertyBrowser()
{
	Q_D(AbstractPropertyBrowser);
	const QList<BrowserItem*> indexes = topLevelItems();
	for (BrowserItem* item : indexes)
		d->clearIndex(item);
}

/*!
	Returns the property browser's list of top level properties.

	To traverse the subproperties, use the PropertySheet::subProperties()
	function.

	\sa addProperty(), insertProperty(), removeProperty()
*/
QList<PropertySheet*> AbstractPropertyBrowser::properties() const
{
	Q_D(const AbstractPropertyBrowser);
	return d->m_subItems;
}

/*!
	Returns the property browser's list of all items associated
	with the given \a property.

	There is one item per instance of the property in the browser.

	\sa topLevelItem()
*/

QList<BrowserItem*> AbstractPropertyBrowser::items(PropertySheet* property) const
{
	Q_D(const AbstractPropertyBrowser);
	return d->m_propertyToIndexes.value(property);
}

/*!
	Returns the top-level items associated with the given \a property.

	Returns 0 if \a property wasn't inserted into this property
	browser or isn't a top-level one.

	\sa topLevelItems(), items()
*/

BrowserItem* AbstractPropertyBrowser::topLevelItem(PropertySheet* property) const
{
	Q_D(const AbstractPropertyBrowser);
	return d->m_topLevelPropertyToIndex.value(property);
}

/*!
	Returns the list of top-level items.

	\sa topLevelItem()
*/

QList<BrowserItem*> AbstractPropertyBrowser::topLevelItems() const
{
	Q_D(const AbstractPropertyBrowser);
	return d->m_topLevelIndexes;
}

/*!
	Removes all the properties from the editor, but does not delete
	them since they can still be used in other editors.

	\sa removeProperty(), QtAbstractPropertyManager::clear()
*/
void AbstractPropertyBrowser::clear()
{
	const QList<PropertySheet*> subList = properties();
	for (auto rit = subList.crbegin(), rend = subList.crend(); rit != rend; ++rit)
		removeProperty(*rit);
}

/*!
	Appends the given \a property (and its subproperties) to the
	property browser's list of top level properties. Returns the item
	created by property browser which is associated with the \a property.
	In order to get all children items created by the property
	browser in this call, the returned item should be traversed.

	If the specified \a property is already added, this function does
	nothing and returns 0.

	\sa insertProperty(), PropertySheet::addSubProperty(), properties()
*/
BrowserItem* AbstractPropertyBrowser::addProperty(PropertySheet* property)
{
	Q_D(AbstractPropertyBrowser);
	PropertySheet* afterProperty = 0;
	if (d->m_subItems.count() > 0)
		afterProperty = d->m_subItems.last();
	return insertProperty(property, afterProperty);
}

/*!
	\fn BrowserItem *AbstractPropertyBrowser::insertProperty(PropertySheet *property,
			PropertySheet *afterProperty)

	Inserts the given \a property (and its subproperties) after
	the specified \a afterProperty in the browser's list of top
	level properties. Returns item created by property browser which
	is associated with the \a property. In order to get all children items
	created by the property browser in this call returned item should be traversed.

	If the specified \a afterProperty is 0, the given \a property is
	inserted at the beginning of the list.  If \a property is
	already inserted, this function does nothing and returns 0.

	\sa addProperty(), PropertySheet::insertSubProperty(), properties()
*/
BrowserItem* AbstractPropertyBrowser::insertProperty(PropertySheet* property,
	PropertySheet* afterProperty)
{
	Q_D(AbstractPropertyBrowser);
	if (!property)
		return 0;

	// if item is already inserted in this item then cannot add.
	QList<PropertySheet*> pendingList = properties();
	int pos = 0;
	int newPos = 0;
	while (pos < pendingList.count()) {
		PropertySheet* prop = pendingList.at(pos);
		if (prop == property)
			return 0;
		if (prop == afterProperty) {
			newPos = pos + 1;
		}
		pos++;
	}
	d->createBrowserIndexes(property, 0, afterProperty);

	// traverse inserted subtree and connect to manager's signals
	d->insertSubTree(property, 0);

	d->m_subItems.insert(newPos, property);
	//propertyInserted(property, 0, properAfterProperty);
	return topLevelItem(property);
}

/*!
	Removes the specified \a property (and its subproperties) from the
	property browser's list of top level properties. All items
	that were associated with the given \a property and its children
	are deleted.

	Note that the properties are \e not deleted since they can still
	be used in other editors.

	\sa clear(), PropertySheet::removeSubProperty(), properties()
*/
void AbstractPropertyBrowser::removeProperty(PropertySheet* property)
{
	Q_D(AbstractPropertyBrowser);
	if (!property)
		return;

	QList<PropertySheet*> pendingList = properties();
	int pos = 0;
	while (pos < pendingList.count()) {
		if (pendingList.at(pos) == property) {
			d->m_subItems.removeAt(pos); //perhaps this two lines
			d->removeSubTree(property, 0); //should be moved down after propertyRemoved call.
			//propertyRemoved(property, 0);

			d->removeBrowserIndexes(property, 0);

			// when item is deleted, item will call removeItem for top level items,
			// and itemRemoved for nested items.

			return;
		}
		pos++;
	}
}

/*!
	Creates an editing widget (with the given \a parent) for the given
	\a property according to the previously established associations
	between property managers and editor factories.

	If the property is created by a property manager which was not
	associated with any of the existing factories in \e this property
	editor, the function returns 0.

	To make a property editable in the property browser, the
	createEditor() function must be called to provide the
	property with a suitable editing widget.

	Reimplement this function to provide additional decoration for the
	editing widgets created by the installed factories.

	\sa setFactoryForManager()
*/
QWidget* AbstractPropertyBrowser::createEditor(PropertySheet* property,
	QWidget* parent)
{
	AbstractEditorFactoryBase* factory = 0;
	AbstractPropertyManager* manager = property->propertyManager();

	if (m_viewToManagerToFactory()->contains(this) &&
		(*m_viewToManagerToFactory())[this].contains(manager)) {
		factory = (*m_viewToManagerToFactory())[this][manager];
	}

	if (!factory)
		return 0;
	QWidget* w = factory->createEditor(property, parent);
	// Since some editors can be QComboBoxes, and we changed their focus policy in Qt 5
	// to make them feel more native on Mac, we need to relax the focus policy to something
	// more permissive to keep the combo box from losing focus, allowing it to stay alive,
	// when the user clicks on it to show the popup.
	if (w)
		w->setFocusPolicy(Qt::WheelFocus);
	return w;
}

bool AbstractPropertyBrowser::addFactory(AbstractPropertyManager* abstractManager,
	AbstractEditorFactoryBase* abstractFactory)
{
	bool connectNeeded = false;
	if (!m_managerToFactoryToViews()->contains(abstractManager) ||
		!(*m_managerToFactoryToViews())[abstractManager].contains(abstractFactory)) {
		connectNeeded = true;
	}
	else if ((*m_managerToFactoryToViews())[abstractManager][abstractFactory]
		.contains(this)) {
		return connectNeeded;
	}

	if (m_viewToManagerToFactory()->contains(this) &&
		(*m_viewToManagerToFactory())[this].contains(abstractManager)) {
		unsetFactoryForManager(abstractManager);
	}

	(*m_managerToFactoryToViews())[abstractManager][abstractFactory].append(this);
	(*m_viewToManagerToFactory())[this][abstractManager] = abstractFactory;

	return connectNeeded;
}

/*!
	Removes the association between the given \a manager and the
	factory bound to it, automatically calling the
	QtAbstractEditorFactory::removePropertyManager() function if necessary.

	\sa setFactoryForManager()
*/
void AbstractPropertyBrowser::unsetFactoryForManager(AbstractPropertyManager* manager)
{
	if (!m_viewToManagerToFactory()->contains(this) ||
		!(*m_viewToManagerToFactory())[this].contains(manager)) {
		return;
	}

	AbstractEditorFactoryBase* abstractFactory =
		(*m_viewToManagerToFactory())[this][manager];
	(*m_viewToManagerToFactory())[this].remove(manager);
	if ((*m_viewToManagerToFactory())[this].isEmpty()) {
		(*m_viewToManagerToFactory()).remove(this);
	}

	(*m_managerToFactoryToViews())[manager][abstractFactory].removeAll(this);
	if ((*m_managerToFactoryToViews())[manager][abstractFactory].isEmpty()) {
		(*m_managerToFactoryToViews())[manager].remove(abstractFactory);
		abstractFactory->breakConnection(manager);
		if ((*m_managerToFactoryToViews())[manager].isEmpty()) {
			(*m_managerToFactoryToViews()).remove(manager);
		}
	}
}

/*!
	Returns the current item in the property browser.

	\sa setCurrentItem()
*/
BrowserItem* AbstractPropertyBrowser::currentItem() const
{
	Q_D(const AbstractPropertyBrowser);
	return d->m_currentItem;
}

/*!
	Sets the current item in the property browser to \a item.

	\sa currentItem(), currentItemChanged()
*/
void AbstractPropertyBrowser::setCurrentItem(BrowserItem* item)
{
	Q_D(AbstractPropertyBrowser);
	BrowserItem* oldItem = d->m_currentItem;
	d->m_currentItem = item;
	if (oldItem != item)
		emit  currentItemChanged(item);
}


