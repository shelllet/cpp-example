#pragma once
#include <pugixml.hpp>
#include <qhash.h>
#include "common.hpp"

namespace shelllet {
	namespace model {
		class ActivitiesDomItemPrivate;
		class ActivitiesDomItem : public Object
		{
			Q_DECLARE_PRIVATE(ActivitiesDomItem)
		public:
			ActivitiesDomItem(const XmlNode& node, int row, int depth, ActivitiesDomItem* parent = nullptr);
			~ActivitiesDomItem();
			ActivitiesDomItem* child(int i);
			ActivitiesDomItem* parent();
			XmlNode node() const;
			int row() const;

		private:

		};
	}
}