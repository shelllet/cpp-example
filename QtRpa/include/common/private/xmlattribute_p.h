#pragma once
#include "object_p.h"
#include "private/qobject_p.h"

namespace shelllet {
	namespace common {
		using namespace pugi;
		class XmlNode;
		class XmlAttributePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(XmlAttribute)
		public:
			UniquePointer< xml_attribute> attr{ new xml_attribute };
		};
	}
}
