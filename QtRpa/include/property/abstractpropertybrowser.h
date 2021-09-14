#pragma once
#include "qwidget.h"
namespace shelllet {
	namespace property {
		class BrowserItem;
		class PropertySheet;
		template<typename T> class AbstractEditorFactory;
		class AbstractEditorFactoryBase;
		class AbstractPropertyManager;
		class AbstractPropertyBrowserPrivate;
		class AbstractPropertyBrowser : public QWidget/*, private boost::noncopyable*/ {
				Q_OBJECT
				Q_DECLARE_PRIVATE(AbstractPropertyBrowser)
		public:

			explicit AbstractPropertyBrowser(QWidget* parent = 0);
			~AbstractPropertyBrowser();

			QList<PropertySheet*> properties() const;
			QList<BrowserItem*> items(PropertySheet* property) const;
			BrowserItem* topLevelItem(PropertySheet* property) const;
			QList<BrowserItem*> topLevelItems() const;
			void clear();

			template <class PropertyManager>
			void setFactoryForManager(PropertyManager* manager,
				AbstractEditorFactory<PropertyManager>* factory) {
				AbstractPropertyManager* abstractManager = manager;
				AbstractEditorFactoryBase* abstractFactory = factory;

				if (addFactory(abstractManager, abstractFactory))
					factory->addPropertyManager(manager);
			}

			void unsetFactoryForManager(AbstractPropertyManager* manager);

			BrowserItem* currentItem() const;
			void setCurrentItem(BrowserItem*);

			signals:
				void currentItemChanged(BrowserItem* item);
		public slots:

			BrowserItem* addProperty(PropertySheet* property);
			BrowserItem* insertProperty(PropertySheet* property, PropertySheet* afterProperty);
			void removeProperty(PropertySheet* property);

		protected:

			virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem) = 0;
			virtual void itemRemoved(BrowserItem* item) = 0;
			// can be tooltip, statustip, whatsthis, name, icon, text.
			virtual void itemChanged(BrowserItem* item) = 0;

			virtual QWidget* createEditor(PropertySheet* property, QWidget* parent);
		private:

			bool addFactory(AbstractPropertyManager* abstractManager,
				AbstractEditorFactoryBase* abstractFactory);

			//	QScopedPointer<AbstractPropertyBrowserPrivate> d_ptr;
				//Q_DECLARE_PRIVATE(QtAbstractPropertyBrowser)
				//	Q_DISABLE_COPY_MOVE(QtAbstractPropertyBrowser)
			/*Q_PRIVATE_SLOT(d_func(), void slotPropertyInserted(PropertySheet*,
				PropertySheet*, PropertySheet*))
				Q_PRIVATE_SLOT(d_func(), void slotPropertyRemoved(PropertySheet*,
					PropertySheet*))
				Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(PropertySheet*))
				Q_PRIVATE_SLOT(d_func(), void slotPropertyDataChanged(PropertySheet*))*/
		protected:
			AbstractPropertyBrowser(AbstractPropertyBrowserPrivate& d, QWidget* parent = nullptr);
		};
	}
}
