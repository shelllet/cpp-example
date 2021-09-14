#pragma once
namespace shelllet {
    namespace property{
        class AbstractPropertyManagerPrivate : public QObjectPrivate {
            Q_DECLARE_PUBLIC(AbstractPropertyManager)
        public:
			//QtAbstractPropertyManager* q_ptr;
			//Q_DECLARE_PUBLIC(QtAbstractPropertyManager)
		public:
			void propertyDestroyed(PropertySheet* property);
			void propertyChanged(PropertySheet* property) ;
			void propertyRemoved(PropertySheet* property,
				PropertySheet* parentProperty) ;
			void propertyInserted(PropertySheet* property, PropertySheet* parentProperty,
				PropertySheet* afterProperty);

			QSet<PropertySheet*> m_properties;
        };
    }
}
