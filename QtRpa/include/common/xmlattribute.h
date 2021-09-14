#pragma once
#include "string.h"
namespace pugi { class xml_attribute; }
namespace shelllet {
	namespace common {
		class XmlAttributePrivate;
		class XmlAttribute : public Object {
			Q_DECLARE_PRIVATE(XmlAttribute)
		public:
			XmlAttribute(Object* parent = nullptr);
			XmlAttribute& operator=(const String& rhs);
			XmlAttribute& operator=(int32_t rhs);
			/*	xml_attribute& operator=(unsigned int rhs);
			xml_attribute& operator=(long rhs);
			xml_attribute& operator=(unsigned long rhs);
			xml_attribute& operator=(double rhs);
			xml_attribute& operator=(float rhs);
			xml_attribute& operator=(bool rhs);*/

			String	value() const;
			void setValue(const String& rhs);
		protected:
			XmlAttribute(XmlAttributePrivate& d, Object* parent = nullptr);

		public:
			static XmlAttribute from(const pugi::xml_attribute* attr);
		};
	}
}
