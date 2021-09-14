#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
		class AbstractPropertyManager;
        class PropertySheetPrivate : public ObjectPrivate {
            Q_DECLARE_PUBLIC(PropertySheet)
		public:
			PropertySheetPrivate(AbstractPropertyManager* manager) : m_enabled(true), m_modified(false), m_manager(manager) {}
			PropertySheet* q_ptr;

			QSet<PropertySheet*> m_parentItems;
			QList<PropertySheet*> m_subItems;

			QString m_valueToolTip;
			QString m_descriptionToolTip;
			QString m_statusTip;
			QString m_whatsThis;
			QString m_name;
			bool m_enabled;
			bool m_modified;

			AbstractPropertyManager* const m_manager;
        };
    }
}
