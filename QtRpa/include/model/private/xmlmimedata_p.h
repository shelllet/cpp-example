#pragma once
#include "common/private/mimedata_p.h"
#include "pugixml.hpp"

class QGraphicsItem;
namespace shelllet {
	namespace model {
		class XmlMimeDataPrivate : public MimeDataPrivate {
			Q_DECLARE_PUBLIC(XmlMimeData)
		public:

			XmlDocument doc;

			QGraphicsItem* source = nullptr;
		};
	}
}
