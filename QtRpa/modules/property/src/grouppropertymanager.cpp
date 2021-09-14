#include "property/framework.h"
#include "property/abstractpropertymanager.h"
#include "property/grouppropertymanager.h"
#include "private/qobject_p.h"
#include "property/private/abstractpropertymanager_p.h"
#include "property/private/grouppropertymanager_p.h"
#include "common/wobjectimpl.h"
namespace shelllet {
	namespace property {



	}
}
using namespace shelllet::property;

W_OBJECT_IMPL(GroupPropertyManager)
//GroupPropertyManager::GroupPropertyManager(Object* parent /*= nullptr*/)
//    :GroupPropertyManager(*new GroupPropertyManagerPrivate,nullptr, parent)
//{
//
//}

GroupPropertyManager::GroupPropertyManager(QObject* parent /*= 0*/)
	: GroupPropertyManager(*new GroupPropertyManagerPrivate, parent)
{

}
GroupPropertyManager::GroupPropertyManager(GroupPropertyManagerPrivate& d, QObject* parent1, Object* parent /*= nullptr*/)
	: AbstractPropertyManager(d, parent1)
{

}


// QtGroupPropertyManager

/*!
	\class QtGroupPropertyManager
	\internal
	\inmodule QtDesigner
	\since 4.4

	\brief The QtGroupPropertyManager provides and manages group properties.

	This class is intended to provide a grouping element without any value.

	\sa AbstractPropertyManager
*/

/*!
	Creates a manager with the given \a parent.
*/

/*!
	Destroys this manager, and all the properties it has created.
*/

/*!
	\reimp
*/
bool GroupPropertyManager::hasValue(const PropertySheet* property) const
{
	Q_UNUSED(property);
	return false;
}

/*!
	\reimp
*/
void GroupPropertyManager::initializeProperty(PropertySheet* property)
{
	Q_UNUSED(property);
}

/*!
	\reimp
*/
void GroupPropertyManager::uninitializeProperty(PropertySheet* property)
{
	Q_UNUSED(property);
}