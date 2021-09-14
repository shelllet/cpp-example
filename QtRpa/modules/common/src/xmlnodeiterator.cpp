#include "pugixml.hpp"
#include "common/xmlnodeiterator.h"
#include "common/private/xmlnode_p.h"
#include "common/private/xmlnodeiterator_p.h"

shelllet::common::XmlNodeIterator::XmlNodeIterator(Object* parent /*= nullptr*/)
	: XmlNodeIterator(*new XmlNodeIteratorPrivate, parent)
{

}

const shelllet::common::XmlNodeIterator& shelllet::common::XmlNodeIterator::operator++()
{
	Q_D(XmlNodeIterator);
	d->iter->operator++();
	return *this;
}

const shelllet::common::XmlNodeIterator& shelllet::common::XmlNodeIterator::operator--()
{
	Q_D(XmlNodeIterator);
	d->iter->operator--();
	return *this;
}

shelllet::common::XmlNodeIterator shelllet::common::XmlNodeIterator::from(pugi::xml_node_iterator* iter)
{
	XmlNodeIterator temp;
	temp.d_func()->iter.reset(new xml_node_iterator(*iter));
	return temp;
}

shelllet::common::XmlNodeIterator shelllet::common::XmlNodeIterator::operator--(int)
{
	Q_D(XmlNodeIterator);
	d->iter->operator--(0);
	return *this;
}

shelllet::common::XmlNodeIterator shelllet::common::XmlNodeIterator::operator++(int)
{
	Q_D(XmlNodeIterator);
	d->iter->operator++(0);
	return *this;
}

bool shelllet::common::XmlNodeIterator::operator!=(const XmlNodeIterator& rhs) const
{
	Q_D(const XmlNodeIterator);
	return *d->iter != *rhs.d_func()->iter;
}

bool shelllet::common::XmlNodeIterator::operator==(const XmlNodeIterator& rhs) const
{
	Q_D(const XmlNodeIterator);
	return *d->iter == *rhs.d_func()->iter;
}

shelllet::common::XmlNode& shelllet::common::XmlNodeIterator::operator*() const
{
	Q_D(const XmlNodeIterator);
	d->node = XmlNode::from(d->iter->operator ->());
	return d->node;
}

shelllet::common::XmlNode* shelllet::common::XmlNodeIterator::operator->() const
{
	Q_D(const XmlNodeIterator);
	d->node = XmlNode::from(d->iter->operator ->());
	return &d->node;
}

shelllet::common::XmlNodeIterator::XmlNodeIterator(const XmlNode& node, Object* parent /*= nullptr*/)
	: XmlNodeIterator(*new XmlNodeIteratorPrivate, parent)
{
	Q_D(XmlNodeIterator);
	d->iter.reset(new xml_node_iterator(*std::get<0>(node.d_func()->node)));
}

shelllet::common::XmlNodeIterator::XmlNodeIterator(const XmlNodeIterator& iter, Object* parent /*= nullptr*/)
	: XmlNodeIterator(*new XmlNodeIteratorPrivate, parent)
{
	Q_D(XmlNodeIterator);
	d->iter.reset(new xml_node_iterator(*iter.d_func()->iter));
}

shelllet::common::XmlNodeIterator::XmlNodeIterator(XmlNodeIteratorPrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{

}
