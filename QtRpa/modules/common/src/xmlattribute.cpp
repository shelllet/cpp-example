#include "common/xmlattribute.h"
#include "pugixml.hpp"
#include "common/private/xmlattribute_p.h"
shelllet::common::XmlAttribute::XmlAttribute(XmlAttributePrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}

shelllet::common::XmlAttribute shelllet::common::XmlAttribute::from(const pugi::xml_attribute* attr)
{
	XmlAttribute temp;
	temp.d_func()->attr.reset(new xml_attribute(*attr));
	return temp;
}

shelllet::common::XmlAttribute& shelllet::common::XmlAttribute::operator=(const String& rhs)
{
	Q_D(XmlAttribute);
	*d->attr = rhs.toUtf8();
	return *this;
}

shelllet::common::XmlAttribute& shelllet::common::XmlAttribute::operator=(int32_t rhs)
{
	Q_D(XmlAttribute);
	*d->attr = rhs;
	return *this;
}

shelllet::common::String shelllet::common::XmlAttribute::value() const
{
	Q_D(const XmlAttribute);

	return d->attr->value();
}

void shelllet::common::XmlAttribute::setValue(const String& rhs)
{
	Q_D(XmlAttribute);
	d->attr->set_value(rhs.toUtf8());
}

shelllet::common::XmlAttribute::XmlAttribute(Object* parent /*= nullptr*/)
	: XmlAttribute(*new XmlAttributePrivate, parent)
{

}
