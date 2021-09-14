#pragma once
#include "object.h"
#include "xmlnode.h"
namespace pugi { class xml_node_iterator;  class xml_node; }

namespace shelllet {
	namespace common {
		class XmlNode;
		class XmlNodeIteratorPrivate;

		class XmlNodeIterator : public Object {
			Q_DECLARE_PRIVATE(XmlNodeIterator)
		public:
			using  difference_type = std::ptrdiff_t;
			using  value_type = XmlNodeIterator;
			using pointer = XmlNodeIterator*;
			using reference = XmlNodeIterator&;
			using iterator_category = std::bidirectional_iterator_tag;

			XmlNodeIterator(Object* parent=nullptr);
			XmlNodeIterator(const XmlNodeIterator& iter, Object* parent = nullptr);
			XmlNodeIterator(const XmlNode& node, Object* parent = nullptr);

			XmlNode& operator *() const;
			XmlNode* operator ->() const;

			bool operator==(const XmlNodeIterator& rhs) const;
			bool operator!=(const XmlNodeIterator& rhs) const;

			const XmlNodeIterator& operator++();
			XmlNodeIterator operator++(int);

			const XmlNodeIterator& operator--();
			XmlNodeIterator operator--(int);


			static XmlNodeIterator from(pugi::xml_node_iterator* iter);
		protected:
			XmlNodeIterator(XmlNodeIteratorPrivate& d, Object* parent = nullptr);
		};

	}
}
