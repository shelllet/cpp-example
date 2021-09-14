#pragma once

namespace shelllet {
	namespace model {
		class ActivitiesDomItemPrivate : public ObjectPrivate {
		public:
			XmlNode domNode;
			QHash<int, ActivitiesDomItem*> childItems;
			ActivitiesDomItem* parentItem;
			int rowNumber;
			int depth;
		};
	}
}