#include "common.hpp"
#include "pugixml.hpp"
#include "common/xmlnodeiterator.h"
#include "common/private/xmlnode_p.h"


namespace shelllet {
	namespace common {
		template <typename F, typename... TArgs>
		decltype(auto) __invoke__(const XmlNodePrivate* p, F fuc, TArgs&& ... args) {
			if (std::holds_alternative<SharedPointer<pugi::xml_node>>(p->node)) {
				return (*std::get<0>(p->node).*fuc)(std::forward<TArgs>(args)...);
			}
			return (*std::get<1>(p->node).*fuc)(std::forward<TArgs>(args)...);
		}
		std::ostream& operator<<(std::ostream& out, const XmlNode& node)
		{
			__invoke__(node.d_func(), static_cast<void(pugi::xml_node::*)(std::basic_ostream<char, std::char_traits<char> >&
				, const char*
				, unsigned int
				, pugi::xml_encoding
				, unsigned int) const>(&pugi::xml_node::print), out, "\t", pugi::format_default, pugi::encoding_auto, 0);
			return out;
		}


	}
}




shelllet::common::XmlNode shelllet::common::XmlNode::appendChild(XmlNodeType type/*= XmlNodeType::Element*/)
{
	Q_D(XmlNode);
	__invoke__(d, static_cast<pugi::xml_node(pugi::xml_node::*)(pugi::xml_node_type)>(&pugi::xml_node::append_child), static_cast<pugi::xml_node_type>(type));
	return *this;
}


void shelllet::common::XmlNode::setValue(const String& value)
{
	Q_D(XmlNode);
	__invoke__(d, &pugi::xml_node::set_value, value.toUtf8());
}

bool shelllet::common::XmlNode::setName(const String& name)
{
	Q_D(XmlNode);
	return __invoke__(d, &pugi::xml_node::set_name, name.toUtf8());
}

shelllet::common::XmlNode shelllet::common::XmlNode::appendChild(const String& name)
{
	Q_D(XmlNode);
	auto node = __invoke__(d, static_cast<pugi::xml_node(pugi::xml_node::*)(const char*)>(&pugi::xml_node::append_child), name.toUtf8());

	return XmlNode::from(&node);
}

shelllet::common::XmlNode shelllet::common::XmlNode::appendCopy(const XmlNode& proto)
{
	Q_D(XmlNode);
	auto node = __invoke__(d, static_cast<pugi::xml_node(pugi::xml_node::*)(const pugi::xml_node&)>(&pugi::xml_node::append_copy), *std::get<0>(proto.d_func()->node));
	return XmlNode::from(&node);
}

shelllet::common::XmlAttribute shelllet::common::XmlNode::appendAttribute(const String& name)
{
	Q_D(XmlNode);
	auto attr = __invoke__(d, &pugi::xml_node::append_attribute, name.toUtf8());
	return XmlAttribute::from(&attr);
}

shelllet::common::XmlAttribute shelllet::common::XmlNode::attribute(const String& name) const
{
	Q_D(const XmlNode);
	auto temp = __invoke__(d, static_cast<pugi::xml_attribute(pugi::xml_node::*)(const char*) const>(&pugi::xml_node::attribute), name.toUtf8());
	return XmlAttribute::from(&temp);
}

shelllet::common::XmlNode shelllet::common::XmlNode::parent() const
{
	Q_D(const XmlNode);
	auto temp = __invoke__(d, &pugi::xml_node::parent);
	return XmlNode::from(&temp);
}

shelllet::common::XmlNodeRange<XmlNodeIterator> shelllet::common::XmlNode::children() const
{
	Q_D(const XmlNode);

	return XmlNodeRange< XmlNodeIterator>(begin(), end());

}

shelllet::common::String shelllet::common::XmlNode::name() const
{
	Q_D(const XmlNode);
	return __invoke__(d, &pugi::xml_node::name);
}

shelllet::common::XmlNodeType shelllet::common::XmlNode::type() const
{
	Q_D(const XmlNode);
	return static_cast<XmlNodeType>(__invoke__(d, &pugi::xml_node::type));
}

shelllet::common::XmlNodeIterator shelllet::common::XmlNode::begin() const
{
	Q_D(const XmlNode);
	auto temp = __invoke__(d, &pugi::xml_node::begin);
	return XmlNodeIterator::from(&temp);
}

shelllet::common::XmlNodeIterator shelllet::common::XmlNode::end() const
{
	Q_D(const XmlNode);
	auto temp = __invoke__(d, &pugi::xml_node::end);
	return XmlNodeIterator::from(&temp);
}

shelllet::common::XmlNode& shelllet::common::XmlNode::operator=(const XmlNode& node)
{
	Q_D(XmlNode);

	std::get<0>(d->node).reset(new pugi::xml_node(*std::get<0>(node.d_func()->node)));
	return *this;
}

shelllet::common::XmlNode::XmlNode(const XmlNode& node, Object* parent/* = nullptr*/)
	: XmlNode(*new XmlNodePrivate, parent)
{
	Q_D(XmlNode);
	std::get<0>(d->node).reset(new pugi::xml_node(*std::get<0>(node.d_func()->node)));
}



shelllet::common::XmlNode::XmlNode(Object* parent /*= nullptr*/)
	: XmlNode(*new XmlNodePrivate, parent)
{

}

shelllet::common::XmlNode::XmlNode(XmlNodePrivate& d, Object* parent /*= nullptr*/)
	: Object(d, parent)
{
	d.node = std::make_shared<pugi::xml_node>();
}

shelllet::common::XmlNode shelllet::common::XmlNode::from(const pugi::xml_node* n)
{
	XmlNode node;
	std::get<0>(node.d_func()->node).reset(new pugi::xml_node(*n));
	return node;
}
