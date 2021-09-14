#pragma once
#include "abstractpropertybrowser.h"
namespace shelllet {
	namespace property {
		class ButtonPropertyBrowserPrivate;
		class ButtonPropertyBrowser : public AbstractPropertyBrowser {
			Q_OBJECT
			Q_DECLARE_PRIVATE(ButtonPropertyBrowser)
		public:
			ButtonPropertyBrowser(Object* parent = nullptr);
			//Q_DECLARE_PRIVATE(QtButtonPropertyBrowser)
		public:

			ButtonPropertyBrowser(QWidget* parent = 0);
			~ButtonPropertyBrowser();

			void setExpanded(BrowserItem* item, bool expanded);
			bool isExpanded(BrowserItem* item) const;

		Q_SIGNALS:

			void collapsed(BrowserItem* item);
			void expanded(BrowserItem* item);

		protected:
			virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem);
			virtual void itemRemoved(BrowserItem* item);
			virtual void itemChanged(BrowserItem* item);

		private slots:

			// QScopedPointer<QtButtonPropertyBrowserPrivate> d_ptr;

		   //  Q_DISABLE_COPY_MOVE(QtButtonPropertyBrowser)
			/*Q_PRIVATE_SLOT(d_func(), void slotUpdate())
				Q_PRIVATE_SLOT(d_func(), void slotEditorDestroyed())
				Q_PRIVATE_SLOT(d_func(), void slotToggled(bool))*/
		protected:
			ButtonPropertyBrowser(ButtonPropertyBrowserPrivate& d, QWidget* parent1 = nullptr, Object* parent = nullptr);
		};
	}
}
