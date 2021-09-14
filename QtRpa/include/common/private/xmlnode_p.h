#pragma once

namespace shelllet {
	namespace common {
		class XmlNodePrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(XmlNode)
		public:
			Variant<SharedPointer<pugi::xml_node>, SharedPointer<pugi::xml_document>> node;

		
		};
	
	}
}
