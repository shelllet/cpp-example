#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
        class GroupPropertyManagerPrivate;
        class GroupPropertyManager : public AbstractPropertyManager {
            Q_DECLARE_PRIVATE(GroupPropertyManager)
                W_OBJECT(GroupPropertyManager)
        public:
          //  GroupPropertyManager(Object*parent = nullptr);

			//Q_OBJECT
		public:
            GroupPropertyManager(QObject* parent = 0);
			~GroupPropertyManager() = default;

		protected:
			virtual bool hasValue(const PropertySheet* property) const;

			virtual void initializeProperty(PropertySheet* property);
			virtual void uninitializeProperty(PropertySheet* property);
        protected:
            GroupPropertyManager(GroupPropertyManagerPrivate& d, QObject* parent1, Object*parent = nullptr);
        };
    }
}
    