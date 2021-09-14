#include "property/framework.h"
#include "property/browseritem.h"
#include "property/propertysheet.h"
#include "property/abstractpropertymanager.h"
#include "private/qobject_p.h"
#include "property/private/abstractpropertymanager_p.h"
namespace shelllet{
    namespace property{
        
    }
}
using namespace shelllet::property;
AbstractPropertyManager::AbstractPropertyManager(QObject* parent /*= nullptr*/)
    :AbstractPropertyManager(*new AbstractPropertyManagerPrivate, parent)
{

}
AbstractPropertyManager::AbstractPropertyManager(AbstractPropertyManagerPrivate& d, QObject* parent /*= nullptr*/)
	: QObject(d, parent)
{

}

////////////////////////////////

void AbstractPropertyManagerPrivate::propertyDestroyed(PropertySheet* property)
{
	Q_Q(AbstractPropertyManager);
	if (m_properties.contains(property)) {
		emit q->propertyDestroyed(property);
		q->uninitializeProperty(property);
		m_properties.remove(property);
	}
}

void AbstractPropertyManagerPrivate::propertyChanged(PropertySheet* property)
{
	Q_Q(AbstractPropertyManager);
	emit q->propertyChanged(property);
}

void AbstractPropertyManagerPrivate::propertyRemoved(PropertySheet* property,
	PropertySheet* parentProperty)
{
	Q_Q(AbstractPropertyManager);
	emit q->propertyRemoved(property, parentProperty);
}

void AbstractPropertyManagerPrivate::propertyInserted(PropertySheet* property,
	PropertySheet* parentProperty, PropertySheet* afterProperty)
{
	Q_Q(AbstractPropertyManager);
	emit q->propertyInserted(property, parentProperty, afterProperty);
}

/*!
	\class AbstractPropertyManager
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The AbstractPropertyManager provides an interface for
	property managers.

	A manager can create and manage properties of a given type, and is
	used in conjunction with the AbstractPropertyBrowser class.

	When using a property browser widget, the properties are created
	and managed by implementations of the AbstractPropertyManager
	class. To ensure that the properties' values will be displayed
	using suitable editing widgets, the managers are associated with
	objects of QtAbstractEditorFactory subclasses. The property browser
	will use these associations to determine which factories it should
	use to create the preferred editing widgets.

	The AbstractPropertyManager class provides common functionality
	like creating a property using the addProperty() function, and
	retrieving the properties created by the manager using the
	properties() function. The class also provides signals that are
	emitted when the manager's properties change: propertyInserted(),
	propertyRemoved(), propertyChanged() and propertyDestroyed().

	AbstractPropertyManager subclasses are supposed to provide their
	own type specific API. Note that several ready-made
	implementations are available:

	\list
	\li QtBoolPropertyManager
	\li QtColorPropertyManager
	\li QtDatePropertyManager
	\li QtDateTimePropertyManager
	\li QtDoublePropertyManager
	\li QtEnumPropertyManager
	\li QtFlagPropertyManager
	\li QtFontPropertyManager
	\li QtGroupPropertyManager
	\li QtIntPropertyManager
	\li QtPointPropertyManager
	\li QtRectPropertyManager
	\li QtSizePropertyManager
	\li QtSizePolicyPropertyManager
	\li QtStringPropertyManager
	\li QtTimePropertyManager
	\li QtVariantPropertyManager
	\endlist

	\sa QtAbstractEditorFactoryBase, AbstractPropertyBrowser, PropertySheet
*/

/*!
	\fn void AbstractPropertyManager::propertyInserted(PropertySheet *newProperty,
				PropertySheet *parentProperty, PropertySheet *precedingProperty)

	This signal is emitted when a new subproperty is inserted into an
	existing property, passing pointers to the \a newProperty, \a
	parentProperty and \a precedingProperty as parameters.

	If \a precedingProperty is 0, the \a newProperty was inserted at
	the beginning of the \a parentProperty's subproperties list.

	Note that signal is emitted only if the \a parentProperty is created
	by this manager.

	\sa AbstractPropertyBrowser::itemInserted()
*/

/*!
	\fn void AbstractPropertyManager::propertyChanged(PropertySheet *property)

	This signal is emitted whenever a property's data changes, passing
	a pointer to the \a property as parameter.

	Note that signal is only emitted for properties that are created by
	this manager.

	\sa AbstractPropertyBrowser::itemChanged()
*/

/*!
	\fn void AbstractPropertyManager::propertyRemoved(PropertySheet *property, PropertySheet *parent)

	This signal is emitted when a subproperty is removed, passing
	pointers to the removed \a property and the \a parent property as
	parameters.

	Note that signal is emitted only when the \a parent property is
	created by this manager.

	\sa AbstractPropertyBrowser::itemRemoved()
*/

/*!
	\fn void AbstractPropertyManager::propertyDestroyed(PropertySheet *property)

	This signal is emitted when the specified \a property is about to
	be destroyed.

	Note that signal is only emitted for properties that are created
	by this manager.

	\sa clear(), uninitializeProperty()
*/

/*!
	\fn void AbstractPropertyBrowser::currentItemChanged(QtBrowserItem *current)

	This signal is emitted when the current item changes. The current item is specified by \a current.

	\sa AbstractPropertyBrowser::setCurrentItem()
*/

/*!
	Creates an abstract property manager with the given \a parent.
*/

/*!
	Destroys the manager. All properties created by the manager are
	destroyed.
*/
AbstractPropertyManager::~AbstractPropertyManager()
{
	clear();
}

/*!
	Destroys all the properties that this manager has created.

	\sa propertyDestroyed(), uninitializeProperty()
*/
void AbstractPropertyManager::clear() const
{
	Q_D(const AbstractPropertyManager);
	while (!d->m_properties.isEmpty())
		delete* d->m_properties.cbegin();
}

/*!
	Returns the set of properties created by this manager.

	\sa addProperty()
*/
QSet<PropertySheet*> AbstractPropertyManager::properties() const
{
	Q_D(const AbstractPropertyManager);
	return d->m_properties;
}

/*!
	Returns whether the given \a property has a value.

	The default implementation of this function returns true.

	\sa PropertySheet::hasValue()
*/
bool AbstractPropertyManager::hasValue(const PropertySheet* property) const
{
	Q_UNUSED(property);
	return true;
}

/*!
	Returns an icon representing the current state of the given \a
	property.

	The default implementation of this function returns an invalid
	icon.

	\sa PropertySheet::valueIcon()
*/
QIcon AbstractPropertyManager::valueIcon(const PropertySheet* property) const
{
	Q_UNUSED(property);
	return QIcon();
}

/*!
	Returns a string representing the current state of the given \a
	property.

	The default implementation of this function returns an empty
	string.

	\sa PropertySheet::valueText()
*/
String AbstractPropertyManager::valueText(const PropertySheet* property) const
{
	Q_UNUSED(property);
	return String();
}

/*!
	Creates a property with the given \a name which then is owned by this manager.

	Internally, this function calls the createProperty() and
	initializeProperty() functions.

	\sa initializeProperty(), properties()
*/
PropertySheet* AbstractPropertyManager::addProperty(const String& name)
{
	Q_D(AbstractPropertyManager);
	PropertySheet* property = createProperty();
	if (property) {
		property->setPropertyName(*name.toQString());
		d->m_properties.insert(property);
		initializeProperty(property);
	}
	return property;
}

/*!
	Creates a property.

	The base implementation produce PropertySheet instances; Reimplement
	this function to make this manager produce objects of a PropertySheet
	subclass.

	\sa addProperty(), initializeProperty()
*/
PropertySheet* AbstractPropertyManager::createProperty()
{
	return new PropertySheet(this);
}

/*!
	\fn void AbstractPropertyManager::initializeProperty(PropertySheet *property) = 0

	This function is called whenever a new valid property pointer has
	been created, passing the pointer as parameter.

	The purpose is to let the manager know that the \a property has
	been created so that it can provide additional attributes for the
	new property, e.g. QtIntPropertyManager adds \l
	{QtIntPropertyManager::value()}{value}, \l
	{QtIntPropertyManager::minimum()}{minimum} and \l
	{QtIntPropertyManager::maximum()}{maximum} attributes. Since each manager
	subclass adds type specific attributes, this function is pure
	virtual and must be reimplemented when deriving from the
	AbstractPropertyManager class.

	\sa addProperty(), createProperty()
*/

/*!
	This function is called just before the specified \a property is destroyed.

	The purpose is to let the property manager know that the \a
	property is being destroyed so that it can remove the property's
	additional attributes.

	\sa clear(), propertyDestroyed()
*/
void AbstractPropertyManager::uninitializeProperty(PropertySheet* property)
{
	Q_UNUSED(property);
}

////////////////////////////////////

/*!
	\class QtAbstractEditorFactoryBase
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The QtAbstractEditorFactoryBase provides an interface for
	editor factories.

	An editor factory is a class that is able to create an editing
	widget of a specified type (e.g. line edits or comboboxes) for a
	given PropertySheet object, and it is used in conjunction with the
	AbstractPropertyManager and AbstractPropertyBrowser classes.

	When using a property browser widget, the properties are created
	and managed by implementations of the AbstractPropertyManager
	class. To ensure that the properties' values will be displayed
	using suitable editing widgets, the managers are associated with
	objects of QtAbstractEditorFactory subclasses. The property browser
	will use these associations to determine which factories it should
	use to create the preferred editing widgets.

	Typically, an editor factory is created by subclassing the
	QtAbstractEditorFactory template class which inherits
	QtAbstractEditorFactoryBase. But note that several ready-made
	implementations are available:

	\list
	\li QtCheckBoxFactory
	\li QtDateEditFactory
	\li QtDateTimeEditFactory
	\li QtDoubleSpinBoxFactory
	\li QtEnumEditorFactory
	\li QtLineEditFactory
	\li QtScrollBarFactory
	\li QtSliderFactory
	\li QtSpinBoxFactory
	\li QtTimeEditFactory
	\li QtVariantEditorFactory
	\endlist

	\sa AbstractPropertyManager, AbstractPropertyBrowser
*/

/*!
	\fn virtual QWidget *QtAbstractEditorFactoryBase::createEditor(PropertySheet *property,
		QWidget *parent) = 0

	Creates an editing widget (with the given \a parent) for the given
	\a property.

	This function is reimplemented in QtAbstractEditorFactory template class
	which also provides a pure virtual convenience overload of this
	function enabling access to the property's manager.

	\sa QtAbstractEditorFactory::createEditor()
*/

/*!
	\fn QtAbstractEditorFactoryBase::QtAbstractEditorFactoryBase(QObject *parent = 0)

	Creates an abstract editor factory with the given \a parent.
*/

/*!
	\fn virtual void QtAbstractEditorFactoryBase::breakConnection(AbstractPropertyManager *manager) = 0

	\internal

	Detaches property manager from factory.
	This method is reimplemented in QtAbstractEditorFactory template subclass.
	You don't need to reimplement it in your subclasses. Instead implement more convenient
	QtAbstractEditorFactory::disconnectPropertyManager() which gives you access to particular manager subclass.
*/

/*!
	\fn virtual void QtAbstractEditorFactoryBase::managerDestroyed(QObject *manager) = 0

	\internal

	This method is called when property manager is being destroyed.
	Basically it notifies factory not to produce editors for properties owned by \a manager.
	You don't need to reimplement it in your subclass. This method is implemented in
	QtAbstractEditorFactory template subclass.
*/

/*!
	\class QtAbstractEditorFactory
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The QtAbstractEditorFactory is the base template class for editor
	factories.

	An editor factory is a class that is able to create an editing
	widget of a specified type (e.g. line edits or comboboxes) for a
	given PropertySheet object, and it is used in conjunction with the
	AbstractPropertyManager and AbstractPropertyBrowser classes.

	Note that the QtAbstractEditorFactory functions are using the
	PropertyManager template argument class which can be any
	AbstractPropertyManager subclass. For example:

	\snippet doc/src/snippets/code/tools_shared_qtpropertybrowser_qtpropertybrowser.cpp 0

	Note that QtSpinBoxFactory by definition creates editing widgets
	\e only for properties created by QtIntPropertyManager.

	When using a property browser widget, the properties are created
	and managed by implementations of the AbstractPropertyManager
	class. To ensure that the properties' values will be displayed
	using suitable editing widgets, the managers are associated with
	objects of QtAbstractEditorFactory subclasses. The property browser will
	use these associations to determine which factories it should use
	to create the preferred editing widgets.

	A QtAbstractEditorFactory object is capable of producing editors for
	several property managers at the same time. To create an
	association between this factory and a given manager, use the
	addPropertyManager() function. Use the removePropertyManager() function to make
	this factory stop producing editors for a given property
	manager. Use the propertyManagers() function to retrieve the set of
	managers currently associated with this factory.

	Several ready-made implementations of the QtAbstractEditorFactory class
	are available:

	\list
	\li QtCheckBoxFactory
	\li QtDateEditFactory
	\li QtDateTimeEditFactory
	\li QtDoubleSpinBoxFactory
	\li QtEnumEditorFactory
	\li QtLineEditFactory
	\li QtScrollBarFactory
	\li QtSliderFactory
	\li QtSpinBoxFactory
	\li QtTimeEditFactory
	\li QtVariantEditorFactory
	\endlist

	When deriving from the QtAbstractEditorFactory class, several pure virtual
	functions must be implemented: the connectPropertyManager() function is
	used by the factory to connect to the given manager's signals, the
	createEditor() function is supposed to create an editor for the
	given property controlled by the given manager, and finally the
	disconnectPropertyManager() function is used by the factory to disconnect
	from the specified manager's signals.

	\sa QtAbstractEditorFactoryBase, AbstractPropertyManager
*/

/*!
	\fn QtAbstractEditorFactory::QtAbstractEditorFactory(QObject *parent = 0)

	Creates an editor factory with the given \a parent.

	\sa addPropertyManager()
*/

/*!
	\fn QWidget *QtAbstractEditorFactory::createEditor(PropertySheet *property, QWidget *parent)

	Creates an editing widget (with the given \a parent) for the given
	\a property.
*/

/*!
	\fn void QtAbstractEditorFactory::addPropertyManager(PropertyManager *manager)

	Adds the given \a manager to this factory's set of managers,
	making this factory produce editing widgets for properties created
	by the given manager.

	The PropertyManager type is a template argument class, and represents the chosen
	AbstractPropertyManager subclass.

	\sa propertyManagers(), removePropertyManager()
*/

/*!
	\fn void QtAbstractEditorFactory::removePropertyManager(PropertyManager *manager)

	Removes the given \a manager from this factory's set of
	managers. The PropertyManager type is a template argument class, and may be
	any AbstractPropertyManager subclass.

	\sa propertyManagers(), addPropertyManager()
*/

/*!
	\fn virtual void QtAbstractEditorFactory::connectPropertyManager(PropertyManager *manager) = 0

	Connects this factory to the given \a manager's signals.  The
	PropertyManager type is a template argument class, and represents
	the chosen AbstractPropertyManager subclass.

	This function is used internally by the addPropertyManager() function, and
	makes it possible to update an editing widget when the associated
	property's data changes. This is typically done in custom slots
	responding to the signals emitted by the property's manager,
	e.g. QtIntPropertyManager::valueChanged() and
	QtIntPropertyManager::rangeChanged().

	\sa propertyManagers(), disconnectPropertyManager()
*/

/*!
	\fn virtual QWidget *QtAbstractEditorFactory::createEditor(PropertyManager *manager, PropertySheet *property,
				QWidget *parent) = 0

	Creates an editing widget with the given \a parent for the
	specified \a property created by the given \a manager. The
	PropertyManager type is a template argument class, and represents
	the chosen AbstractPropertyManager subclass.

	This function must be implemented in derived classes: It is
	recommended to store a pointer to the widget and map it to the
	given \a property, since the widget must be updated whenever the
	associated property's data changes. This is typically done in
	custom slots responding to the signals emitted by the property's
	manager, e.g. QtIntPropertyManager::valueChanged() and
	QtIntPropertyManager::rangeChanged().

	\sa connectPropertyManager()
*/

/*!
	\fn virtual void QtAbstractEditorFactory::disconnectPropertyManager(PropertyManager *manager) = 0

	Disconnects this factory from the given \a manager's signals. The
	PropertyManager type is a template argument class, and represents
	the chosen AbstractPropertyManager subclass.

	This function is used internally by the removePropertyManager() function.

	\sa propertyManagers(), connectPropertyManager()
*/

/*!
	\fn QSet<PropertyManager *> QtAbstractEditorFactory::propertyManagers() const

	Returns the factory's set of associated managers.  The
	PropertyManager type is a template argument class, and represents
	the chosen AbstractPropertyManager subclass.

	\sa addPropertyManager(), removePropertyManager()
*/

/*!
	\fn PropertyManager *QtAbstractEditorFactory::propertyManager(PropertySheet *property) const

	Returns the property manager for the given \a property, or 0 if
	the given \a property doesn't belong to any of this factory's
	registered managers.

	The PropertyManager type is a template argument class, and represents the chosen
	AbstractPropertyManager subclass.

	\sa propertyManagers()
*/

/*!
	\fn virtual void QtAbstractEditorFactory::managerDestroyed(QObject *manager)

	\internal
*/

////////////////////////////////////