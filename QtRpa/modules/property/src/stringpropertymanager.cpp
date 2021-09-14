#include "property/framework.h"
#include "property/abstractpropertymanager.h"
#include "property/stringpropertymanager.h"
#include "private/qobject_p.h"
#include "property/private/abstractpropertymanager_p.h"
#include "property/private/stringpropertymanager_p.h"
namespace shelllet{
    namespace property{
		template <class Value, class PrivateData>
		static Value getData(const QMap<const PropertySheet*, PrivateData>& propertyMap,
			Value PrivateData::* data,
			const PropertySheet* property, const Value& defaultValue = Value())
		{
			const auto it = propertyMap.constFind(property);
			if (it == propertyMap.constEnd())
				return defaultValue;
			return it.value().*data;
		}

		template <class Value, class PrivateData>
		static Value getValue(const QMap<const PropertySheet*, PrivateData>& propertyMap,
			const PropertySheet* property, const Value& defaultValue = Value())
		{
			return getData<Value>(propertyMap, &PrivateData::val, property, defaultValue);
		}
    }
}
using namespace shelllet::property;

//StringPropertyManager::StringPropertyManager(Object* parent /*= nullptr*/)
//    :StringPropertyManager(*new StringPropertyManagerPrivate, nullptr, parent)
//{
//
//}
StringPropertyManager::StringPropertyManager(StringPropertyManagerPrivate& d, QObject* parent, Object* /*parent*/ /*= nullptr*/)
	: AbstractPropertyManager(d, parent)
{

}


StringPropertyManager::StringPropertyManager(QObject* parent)
	: AbstractPropertyManager(*new StringPropertyManagerPrivate, parent)
{
}

/*!
	Destroys this manager, and all the properties it has created.
*/
StringPropertyManager::~StringPropertyManager()
{
	clear();
}



/*!
	Returns the given \a property's value.

	If the given property is not managed by this manager, this
	function returns an empty string.

	\sa setValue()
*/
String StringPropertyManager::value(const PropertySheet* property) const
{
	Q_D(const StringPropertyManager);
	return getValue<String>(d->m_values, property);
}

/*!
	Returns the given \a property's currently set regular expression.

	If the given \a property is not managed by this manager, this
	function returns an empty expression.

	\sa setRegExp()
*/
QRegExp StringPropertyManager::regExp(const PropertySheet* property) const
{
	Q_D(const StringPropertyManager);
	return getData<QRegExp>(d->m_values, &StringPropertyManagerPrivate::Data::regExp, property, QRegExp());
}

/*!
	\reimp
*/
String StringPropertyManager::valueText(const PropertySheet* property) const
{
	Q_D(const StringPropertyManager);
	const StringPropertyManagerPrivate::PropertyValueMap::const_iterator it = d->m_values.constFind(property);
	if (it == d->m_values.constEnd())
		return String();
	return it.value().val;
}

/*!
	\fn void StringPropertyManager::setValue(PropertySheet *property, const QString &value)

	Sets the value of the given \a property to \a value.

	If the specified \a value doesn't match the given \a property's
	regular expression, this function does nothing.

	\sa value(), setRegExp(), valueChanged()
*/
void StringPropertyManager::setValue(PropertySheet* property, const String& val)
{
	Q_D(StringPropertyManager);
	const StringPropertyManagerPrivate::PropertyValueMap::iterator it = d->m_values.find(property);
	if (it == d->m_values.end())
		return;

	StringPropertyManagerPrivate::Data data = it.value();

	if (data.val == val)
		return;

	if (data.regExp.isValid() && !data.regExp.exactMatch(*val.toQString()))
		return;

	data.val = val;

	it.value() = data;

	emit propertyChanged(property);
	emit valueChanged(property, data.val);
}
/*!
	Sets the regular expression of the given \a property to \a regExp.

	\sa regExp(), setValue(), regExpChanged()
*/
void StringPropertyManager::setRegExp(PropertySheet* property, const QRegExp& regExp)
{
	Q_D(StringPropertyManager);
	const StringPropertyManagerPrivate::PropertyValueMap::iterator it = d->m_values.find(property);
	if (it == d->m_values.end())
		return;

	StringPropertyManagerPrivate::Data data = it.value();

	if (data.regExp == regExp)
		return;

	data.regExp = regExp;

	it.value() = data;

	emit regExpChanged(property, data.regExp);
}

/*!
	\reimp
*/
void StringPropertyManager::initializeProperty(PropertySheet* property)
{
	Q_D(StringPropertyManager);
	d->m_values[property] = StringPropertyManagerPrivate::Data();
}

/*!
	\reimp
*/
void StringPropertyManager::uninitializeProperty(PropertySheet* property)
{
	Q_D(StringPropertyManager);
	d->m_values.remove(property);
}