#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
        class GroupBoxPropertyBrowserPrivate;
        class GroupBoxPropertyBrowser : public AbstractPropertyBrowser {
            Q_DECLARE_PRIVATE(GroupBoxPropertyBrowser)
        public:
            GroupBoxPropertyBrowser(Object*parent = nullptr);

			Q_OBJECT
		public:

			GroupBoxPropertyBrowser(QWidget* parent = 0);
			~GroupBoxPropertyBrowser();

		protected:
			virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem);
			virtual void itemRemoved(BrowserItem* item);
			virtual void itemChanged(BrowserItem* item);

		private:

			//QScopedPointer<QtGroupBoxPropertyBrowserPrivate> d_ptr;
			//Q_DECLARE_PRIVATE(QtGroupBoxPropertyBrowser)
			//	Q_DISABLE_COPY_MOVE(QtGroupBoxPropertyBrowser)
				//Q_PRIVATE_SLOT(d_func(), void slotUpdate())
				//Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
        protected:
            GroupBoxPropertyBrowser(GroupBoxPropertyBrowserPrivate& d, QWidget* widget = nullptr, Object*parent = nullptr);
        };
    }
}
    