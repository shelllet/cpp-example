#pragma once
#include "object_p.h"
namespace shelllet {
	namespace common {
		using namespace pugi;
		class XmlNodeIteratorPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(XmlNodeIterator)
		public:
			UniquePointer<xml_node_iterator> iter{ new xml_node_iterator };
			mutable XmlNode node;

		};
	}
}
