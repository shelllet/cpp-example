#pragma once
#include "xmlattribute.h"
#include "xmlnodeiterator.h"
namespace shelllet {
	namespace common {

		template <typename It> class XmlNodeRange
		{
		public:
			typedef It const_iterator;
			typedef It iterator;

			XmlNodeRange(It b, It e) : _begin(b), _end(e)
			{
			}

			It begin() const { return _begin; }
			It end() const { return _end; }

		private:
			It _begin, _end;
		};

		class XmlNodePrivate;
		class XmlNode : public Object {
			Q_DECLARE_PRIVATE(XmlNode)
				friend	std::ostream& operator<< (std::ostream& out, const XmlNode& node);
			friend class XmlNodeIterator;
		public:
			XmlNode(Object* parent = nullptr);
			XmlNode(const XmlNode& node, Object* parent = nullptr);
			XmlNode appendChild(XmlNodeType type = XmlNodeType::Element);
			XmlNode appendChild(const String& name);
			void setValue(const String& value);
			bool setName(const String& name);
			XmlNode appendCopy(const XmlNode& proto);
			XmlAttribute appendAttribute(const String& name);

			XmlAttribute attribute(const String& name) const;

			XmlNode parent() const;
			XmlNodeRange<XmlNodeIterator> children() const;

			String name() const;

			XmlNodeType type() const;



			XmlNodeIterator begin() const;
			XmlNodeIterator end() const;

			XmlNode& operator= (const XmlNode& node);


			/*bool operator==(const XmlNode& r) const;
			bool operator!=(const XmlNode& r) const;
			bool operator<(const XmlNode& r) const;
			bool operator>(const XmlNode& r) const;
			bool operator<=(const XmlNode& r) const;
			bool operator>=(const XmlNode& r) const;*/

		protected:
			XmlNode(XmlNodePrivate& d, Object* parent = nullptr);

		public:
			static XmlNode from(const pugi::xml_node* n);
		};
	}
}
