#include "common.hpp"
#include "property.hpp"
#include "interpreter/property.h"
#include "interpreter/private/property_p.h"


//NamedProperty::NamedProperty(const pugi::xml_node& node, QObject* parent /*= nullptr*/)
//	: QObject(parent)
//{
//}


shelllet::interpreter::Property::Property(const XmlNode& node, QObject* parent /*= nullptr*/)
	: Property(*new PropertyPrivate, node, parent)
{
}

void shelllet::interpreter::Property::initialize()
{
}

//void UniqueNamedProperty::toXml(pugi::xml_node& node)
//{
//	NamedProperty::toXml(node);
//
//	node.append_attribute("meta") = metaName().c_str();
//}
//void UniqueNamedProperty::fromXml(const pugi::xml_node& node)
//{
//	NamedProperty::fromXml(node);
//}

String shelllet::interpreter::Property::displayName() const
{
	Q_D(const Property);
	return d->m_displayName;
}

shelllet::interpreter::Property::Property(QObject* parent /*= nullptr*/)
	: QObject(parent)
{
}

void shelllet::interpreter::Property::deleteLater()
{
	QObject::deleteLater();
}

std::vector<PropertySheet*> shelllet::interpreter::Property::getProp(PropertyBrowser* browser)
{
	return {};
}

PropertySheet* shelllet::interpreter::Property::getMisc(PropertyBrowser* browser)
{
	Q_D(Property);
	GroupPropertyManager* groupManager = new GroupPropertyManager();
	d->m_misc = groupManager->addProperty(String::fromQString(&static_cast<const QString&>(QObject::tr("Misc"))));

	LineEditFactory* lineEdit = new LineEditFactory();
	StringPropertyManager* strManager = new StringPropertyManager();

	PropertySheet* display = strManager->addProperty(String::fromQString(&static_cast<const QString&>(QObject::tr("Display Name"))));

	d->m_misc->addSubProperty(display);

	strManager->setValue(display, displayName());

	connect(strManager, &StringPropertyManager::valueChanged, [this](PropertySheet* property, const String& val) {
		Q_D(Property);
		d->m_displayName = val;
		emit displayNameChanged();
	});

	browser->setFactoryForManager(strManager, lineEdit);
	return d->m_misc;
}

std::shared_ptr<XmlDocument> shelllet::interpreter::Property::getNode()
{
	Q_D(Property);
	auto  doc = std::make_shared<XmlDocument>();
	XmlNode node = doc->appendChild(d->tagName);
	node.appendAttribute("display") = d->m_displayName;
	return doc;
}

QString shelllet::interpreter::Property::metaName() const
{
	std::string name = metaObject()->className();
	std::vector<std::string> result;
	boost::split_regex(result, name, boost::regex("::"));

	return QString::fromStdString(result.back());
}

String shelllet::interpreter::Property::tagName() const
{
	Q_D(const Property);
	return d->tagName;
}

QIcon shelllet::interpreter::Property::icon() const
{
	Q_D(const Property);
	return d->icon;
}

QString shelllet::interpreter::Property::Prefix()
{
	static QString p;
	if (p.isEmpty()) {
		std::string name = Property::staticMetaObject.className();
		std::vector<std::string> vec;
		boost::split_regex(vec, name, boost::regex("::"));

		vec.pop_back();
		p = QString::fromStdString(boost::join(vec, "::"));
	}
	return p;
}

PropertySheet* shelllet::interpreter::Property::getOutput(PropertyBrowser*)
{
	throw std::logic_error("The method or operation is not implemented.");
}

PropertySheet* shelllet::interpreter::Property::getInput(PropertyBrowser*)
{
	throw std::logic_error("The method or operation is not implemented.");
}

//void shelllet::properties::NamedProperty::toXml(pugi::xml_node& node)
//{
//	node.append_attribute("display") = m_displayName.c_str();
//}

//void shelllet::properties::NamedProperty::fromXml(const pugi::xml_node& node)
//{
//	m_displayName = node.attribute("display").value();
//}

//UniqueNamedProperty::UniqueNamedProperty(QObject* parent /*= nullptr*/)
//	: NamedProperty(parent)
//{
//}


shelllet::interpreter::Property::Property(PropertyPrivate& d, const XmlNode& node, QObject* parent /*= nullptr*/)
	: QObject(d, parent)
{
	d.m_displayName = node.attribute("display").value();
	d.icon = Environment::getInstance()->getIconByName(node.attribute("display").value());
	d.tagName = node.name();

	emit displayNameChanged();
}
