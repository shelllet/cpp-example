#pragma once
namespace shelllet {
	namespace property {
		class PropertySheet;
		class AbstractPropertyBrowser;
		class BrowserItemPrivate;
		class BrowserItem : public Object {
			Q_DECLARE_PRIVATE(BrowserItem)
		public:

		public:
			PropertySheet* property() const;
			BrowserItem* parent() const;
			QList<BrowserItem*> children() const;
			AbstractPropertyBrowser* browser() const;
		private:
			explicit BrowserItem(AbstractPropertyBrowser* browser, PropertySheet* property, BrowserItem* parent);
			~BrowserItem();
			//	QScopedPointer<QtBrowserItemPrivate> d_ptr;
			friend class AbstractPropertyBrowserPrivate;
		protected:
			BrowserItem(BrowserItemPrivate& d, Object* parent = nullptr);
		};
	}
}
W_REGISTER_ARGTYPE(shelllet::property::BrowserItem*)

