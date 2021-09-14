#pragma once
#ifdef PropertySheet
#undef PropertySheet
#endif // PropertySheet
namespace shelllet {
	namespace property {
		class AbstractPropertyBrowserPrivate : public QWidgetPrivate {
			Q_DECLARE_PUBLIC(AbstractPropertyBrowser)
		public:
			AbstractPropertyBrowserPrivate();
			void insertSubTree(PropertySheet* property,
				PropertySheet* parentProperty);
			void removeSubTree(PropertySheet* property,
				PropertySheet* parentProperty);
			void createBrowserIndexes(PropertySheet* property, PropertySheet* parentProperty, PropertySheet* afterProperty);
			void removeBrowserIndexes(PropertySheet* property, PropertySheet* parentProperty);
			BrowserItem* createBrowserIndex(PropertySheet* property, BrowserItem* parentIndex, BrowserItem* afterIndex);
			void removeBrowserIndex(BrowserItem* index);
			void clearIndex(BrowserItem* index);

			void slotPropertyInserted(PropertySheet* property,
				PropertySheet* parentProperty, PropertySheet* afterProperty);
			void slotPropertyRemoved(PropertySheet* property, PropertySheet* parentProperty);
			void slotPropertyDestroyed(PropertySheet* property);
			void slotPropertyDataChanged(PropertySheet* property);

			QList<PropertySheet*> m_subItems;
			QMap<AbstractPropertyManager*, QList<PropertySheet*> > m_managerToProperties;
			QMap<PropertySheet*, QList<PropertySheet*> > m_propertyToParents;

			QMap<PropertySheet*, BrowserItem*> m_topLevelPropertyToIndex;
			QList<BrowserItem*> m_topLevelIndexes;
			QMap<PropertySheet*, QList<BrowserItem*> > m_propertyToIndexes;

			BrowserItem* m_currentItem;
		};
	}
}
