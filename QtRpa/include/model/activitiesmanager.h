#pragma once
#include "common.hpp"
namespace shelllet {
	namespace model {
		class ActivitiesManagerPrivate;
		class ActivitiesManager : public QObject {
			Q_DECLARE_PRIVATE(ActivitiesManager)
		public:
			ActivitiesManager(QObject* parent = nullptr);
			void loadAll();
			SharedPointer<XmlDocument> document() const;

			static	ActivitiesManager* getInstance();
		protected:
			ActivitiesManager(ActivitiesManagerPrivate& d, QObject* parent = nullptr);
		};
	}
}
