#pragma once
#include "common.hpp"
class QGraphicsItem;
namespace shelllet {
	namespace model {
		class XmlMimeDataPrivate;
		class XmlMimeData : public MimeData {
			Q_DECLARE_PRIVATE_D(Object::d_ptr,XmlMimeData)
		public:
			XmlMimeData(const XmlNode& node);

			XmlNode documentElement() const;

			void setSourceItem(QGraphicsItem* source);
			QGraphicsItem* sourceItem() const;
		};
	}
}
