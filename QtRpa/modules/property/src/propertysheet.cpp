#include "common.hpp"
#include "property/propertysheet.h"
#include "property/abstractpropertymanager.h"
#include "private/qobject_p.h"
#include "property/private/propertysheet_p.h"
#include "property/private/abstractpropertymanager_p.h"
#include "property/qtpropertybrowser.h"
using namespace shelllet::property;
namespace shelllet {
	namespace property {

	}

}

PropertySheet::PropertySheet(PropertySheetPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}



/*!
	\class PropertySheet
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The PropertySheet class encapsulates an instance of a property.

	Properties are created by objects of QtAbstractPropertyManager
	subclasses; a manager can create properties of a given type, and
	is used in conjunction with the QtAbstractPropertyBrowser class. A
	property is always owned by the manager that created it, which can
	be retrieved using the propertyManager() function.

	PropertySheet contains the most common property attributes, and
	provides functions for retrieving as well as setting their values:

	\table
	\header \li Getter \li Setter
	\row
	\li propertyName() \li setPropertyName()
	\row
	\li statusTip() \li setStatusTip()
	\row
	\li descriptionToolTip() \li setDescriptionToolTip()
	\row
	\li valueToolTip() \li setValueToolTip()
	\row
	\li toolTip() \deprecated in 5.6 \li setToolTip() \deprecated in 5.6
	\row
	\li whatsThis() \li setWhatsThis()
	\row
	\li isEnabled() \li setEnabled()
	\row
	\li isModified() \li setModified()
	\row
	\li valueText() \li Nop
	\row
	\li valueIcon() \li Nop
	\endtable

	It is also possible to nest properties: PropertySheet provides the
	addSubProperty(), insertSubProperty() and removeSubProperty() functions to
	manipulate the set of subproperties. Use the subProperties()
	function to retrieve a property's current set of subproperties.
	Note that nested properties are not owned by the parent property,
	i.e. each subproperty is owned by the manager that created it.

	\sa QtAbstractPropertyManager, QtBrowserItem
*/

/*!
	Creates a property with the given \a manager.

	This constructor is only useful when creating a custom PropertySheet
	subclass (e.g. QtVariantProperty). To create a regular PropertySheet
	object, use the QtAbstractPropertyManager::addProperty()
	function instead.

	\sa QtAbstractPropertyManager::addProperty()
*/
PropertySheet::PropertySheet(AbstractPropertyManager* manager)
	: PropertySheet(*new PropertySheetPrivate(manager), nullptr)
{
}

/*!
	Destroys this property.

	Note that subproperties are detached but not destroyed, i.e. they
	can still be used in another context.

	\sa QtAbstractPropertyManager::clear()

*/
PropertySheet::~PropertySheet()
{
	Q_D(PropertySheet);
	for (PropertySheet* property : qAsConst(d->m_parentItems))
		d->m_manager->d_func()->propertyRemoved(this, property);

	d->m_manager->d_func()->propertyDestroyed(this);

	for (PropertySheet* property : qAsConst(d->m_subItems))
		property->d_func()->m_parentItems.remove(this);

	for (PropertySheet* property : qAsConst(d->m_parentItems))
		property->d_func()->m_subItems.removeAll(this);
}

/*!
	Returns the set of subproperties.

	Note that subproperties are not owned by \e this property, but by
	the manager that created them.

	\sa insertSubProperty(), removeSubProperty()
*/
QList<PropertySheet*> PropertySheet::subProperties() const
{
	Q_D(const PropertySheet);
	return d->m_subItems;
}

/*!
	Returns a pointer to the manager that owns this property.
*/
AbstractPropertyManager* PropertySheet::propertyManager() const
{
	Q_D(const PropertySheet);
	return d->m_manager;
}

/* Note: As of 17.7.2015 for Qt 5.6, the existing 'toolTip' of the Property
 * Browser solution was split into valueToolTip() and descriptionToolTip()
 * to be able to implement custom tool tip for QTBUG-45442. This could
 * be back-ported to the solution. */

 /*!
	 Returns the property value's  tool tip.

	 This is suitable for tool tips over the value (item delegate).

	 \since 5.6
	 \sa setValueToolTip()
 */
QString PropertySheet::valueToolTip() const
{
	Q_D(const PropertySheet);
	return d->m_valueToolTip;
}

/*!
	Returns the property description's  tool tip.

	This is suitable for tool tips over the description (label).

	\since 5.6
	\sa setDescriptionToolTip()
*/
QString PropertySheet::descriptionToolTip() const
{
	Q_D(const PropertySheet);
	return d->m_descriptionToolTip;
}

/*!
	Returns the property's status tip.

	\sa setStatusTip()
*/
QString PropertySheet::statusTip() const
{
	Q_D(const PropertySheet);
	return d->m_statusTip;
}

/*!
	Returns the property's "What's This" help text.

	\sa setWhatsThis()
*/
QString PropertySheet::whatsThis() const
{
	Q_D(const PropertySheet);
	return d->m_whatsThis;
}

/*!
	Returns the property's name.

	\sa setPropertyName()
*/
QString PropertySheet::propertyName() const
{
	Q_D(const PropertySheet);
	return d->m_name;
}

/*!
	Returns whether the property is enabled.

	\sa setEnabled()
*/
bool PropertySheet::isEnabled() const
{
	Q_D(const PropertySheet);
	return d->m_enabled;
}

/*!
	Returns whether the property is modified.

	\sa setModified()
*/
bool PropertySheet::isModified() const
{
	Q_D(const PropertySheet);
	return d->m_modified;
}

/*!
	Returns whether the property has a value.

	\sa QtAbstractPropertyManager::hasValue()
*/
bool PropertySheet::hasValue() const
{
	Q_D(const PropertySheet);
	return d->m_manager->hasValue(this);
}

/*!
	Returns an icon representing the current state of this property.

	If the given property type can not generate such an icon, this
	function returns an invalid icon.

	\sa QtAbstractPropertyManager::valueIcon()
*/
QIcon PropertySheet::valueIcon() const
{
	Q_D(const PropertySheet);
	return d->m_manager->valueIcon(this);
}

/*!
	Returns a string representing the current state of this property.

	If the given property type can not generate such a string, this
	function returns an empty string.

	\sa QtAbstractPropertyManager::valueText()
*/
String PropertySheet::valueText() const
{
	Q_D(const PropertySheet);
	return d->m_manager->valueText(this);
}

/*!
	Sets the property value's tool tip to the given \a text.

	\since 5.6
	\sa valueToolTip()
*/
void PropertySheet::setValueToolTip(const QString& text)
{
	Q_D(PropertySheet);
	if (d->m_valueToolTip == text)
		return;

	d->m_valueToolTip = text;
	propertyChanged();
}

/*!
	Sets the property description's tool tip to the given \a text.

	\since 5.6
	\sa descriptionToolTip()
*/
void PropertySheet::setDescriptionToolTip(const QString& text)
{
	Q_D( PropertySheet);
	if (d->m_descriptionToolTip == text)
		return;

	d->m_descriptionToolTip = text;
	propertyChanged();
}

/*!
	Sets the property's status tip to the given \a text.

	\sa statusTip()
*/
void PropertySheet::setStatusTip(const QString& text)
{
	Q_D(PropertySheet);
	if (d->m_statusTip == text)
		return;

	d->m_statusTip = text;
	propertyChanged();
}

/*!
	Sets the property's "What's This" help text to the given \a text.

	\sa whatsThis()
*/
void PropertySheet::setWhatsThis(const QString& text)
{
	Q_D(PropertySheet);
	if (d->m_whatsThis == text)
		return;

	d->m_whatsThis = text;
	propertyChanged();
}

/*!
	\fn void PropertySheet::setPropertyName(const QString &name)

	Sets the property's  name to the given \a name.

	\sa propertyName()
*/
void PropertySheet::setPropertyName(const QString& text)
{
	Q_D(PropertySheet);
	if (d->m_name == text)
		return;

	d->m_name = text;
	propertyChanged();
}

/*!
	Enables or disables the property according to the passed \a enable value.

	\sa isEnabled()
*/
void PropertySheet::setEnabled(bool enable)
{
	Q_D(PropertySheet);
	if (d->m_enabled == enable)
		return;

	d->m_enabled = enable;
	propertyChanged();
}

/*!
	Sets the property's modified state according to the passed \a modified value.

	\sa isModified()
*/
void PropertySheet::setModified(bool modified)
{
	Q_D(PropertySheet);
	if (d->m_modified == modified)
		return;

	d->m_modified = modified;
	propertyChanged();
}

/*!
	Appends the given \a property to this property's subproperties.

	If the given \a property already is added, this function does
	nothing.

	\sa insertSubProperty(), removeSubProperty()
*/
void PropertySheet::addSubProperty(PropertySheet* property)
{
	Q_D(PropertySheet);
	PropertySheet* after = 0;
	if (d->m_subItems.count() > 0)
		after = d->m_subItems.last();
	insertSubProperty(property, after);
}

/*!
	\fn void PropertySheet::insertSubProperty(PropertySheet *property, PropertySheet *precedingProperty)

	Inserts the given \a property after the specified \a
	precedingProperty into this property's list of subproperties.  If
	\a precedingProperty is 0, the specified \a property is inserted
	at the beginning of the list.

	If the given \a property already is inserted, this function does
	nothing.

	\sa addSubProperty(), removeSubProperty()
*/
void PropertySheet::insertSubProperty(PropertySheet* property,
	PropertySheet* afterProperty)
{
	Q_D(PropertySheet);
	if (!property)
		return;

	if (property == this)
		return;

	// traverse all children of item. if this item is a child of item then cannot add.
	QList<PropertySheet*> pendingList = property->subProperties();
	QMap<PropertySheet*, bool> visited;
	while (!pendingList.isEmpty()) {
		PropertySheet* i = pendingList.first();
		if (i == this)
			return;
		pendingList.removeFirst();
		if (visited.contains(i))
			continue;
		visited[i] = true;
		pendingList += i->subProperties();
	}

	pendingList = subProperties();
	int pos = 0;
	int newPos = 0;
	PropertySheet* properAfterProperty = 0;
	while (pos < pendingList.count()) {
		PropertySheet* i = pendingList.at(pos);
		if (i == property)
			return; // if item is already inserted in this item then cannot add.
		if (i == afterProperty) {
			newPos = pos + 1;
			properAfterProperty = afterProperty;
		}
		pos++;
	}

	d->m_subItems.insert(newPos, property);
	property->d_func()->m_parentItems.insert(this);

	d->m_manager->d_func()->propertyInserted(property, this, properAfterProperty);
}

/*!
	Removes the given \a property from the list of subproperties
	without deleting it.

	\sa addSubProperty(), insertSubProperty()
*/
void PropertySheet::removeSubProperty(PropertySheet* property)
{
	Q_D(PropertySheet);
	if (!property)
		return;

	d->m_manager->d_func()->propertyRemoved(property, this);

	QList<PropertySheet*> pendingList = subProperties();
	int pos = 0;
	while (pos < pendingList.count()) {
		if (pendingList.at(pos) == property) {
			d->m_subItems.removeAt(pos);
			property->d_func()->m_parentItems.remove(this);

			return;
		}
		pos++;
	}
}

/*!
	\internal
*/
void PropertySheet::propertyChanged()
{
	Q_D(PropertySheet);
	d->m_manager->d_func()->propertyChanged(this);
}
