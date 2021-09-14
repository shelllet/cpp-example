#include "properties.hpp"
#include "properties/sequence.h"
#include "properties/private/sequence_p.h"

shelllet::properties::Sequence::Sequence(const XmlNode& node, QObject* parent /*= nullptr*/)
	: CompositeProperty(*new SequencePrivate, node, parent)
{
	Q_D(Sequence);
	d->m_displayName = "Sequence";
	d->tagName = "sequence";
}


void shelllet::properties::Sequence::getCode(std::ostringstream& oss)
{
	throw std::logic_error("The method or operation is not implemented.");
}


//std::string shelllet::properties::Sequence::getImport() const
//{
//	throw std::logic_error("The method or operation is not implemented.");
//}

//std::unique_ptr<pugi::xml_document> shelllet::properties::Sequence::getNode()
//{
//	Q_D(Sequence);
//
//	auto doc = __super::getNode();
//	return doc;
//}