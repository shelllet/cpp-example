#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
		class PropertySheet;
        class AbstractPropertyManagerPrivate;
        class AbstractPropertyManager : public QObject, private boost::noncopyable {
			Q_OBJECT
            Q_DECLARE_PRIVATE(AbstractPropertyManager)
        public:
            //AbstractPropertyManager(Object*parent = nullptr);

		public:

			explicit AbstractPropertyManager(QObject* parent = 0);
			~AbstractPropertyManager();

			QSet<PropertySheet*> properties() const;
			void clear() const;

			PropertySheet* addProperty(const String& name);
		signals:

			void propertyInserted(PropertySheet* property, PropertySheet* parent, PropertySheet* after);

			void propertyChanged(PropertySheet* property);
			void propertyRemoved(PropertySheet* property, PropertySheet* parent);
			void propertyDestroyed(PropertySheet* property);
		protected:
			virtual bool hasValue(const PropertySheet* property) const;
			virtual QIcon valueIcon(const PropertySheet* property) const;
			virtual String valueText(const PropertySheet* property) const;
			virtual void initializeProperty(PropertySheet* property) = 0;
			virtual void uninitializeProperty(PropertySheet* property);
			virtual PropertySheet* createProperty();
		private:
			friend class PropertySheet;
			//QScopedPointer<AbstractPropertyManagerPrivate> d_ptr;
			//Q_DECLARE_PRIVATE(QtAbstractPropertyManager)
				//Q_DISABLE_COPY_MOVE(QtAbstractPropertyManager)
        protected:
            AbstractPropertyManager(AbstractPropertyManagerPrivate& d, QObject*parent = nullptr);
        };
    }
}
    