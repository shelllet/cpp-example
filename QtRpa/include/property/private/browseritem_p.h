#pragma once
#ifdef PropertySheet
#undef PropertySheet
#endif // PropertySheet
namespace shelllet {
    namespace property{
        class BrowserItemPrivate : public ObjectPrivate {
            Q_DECLARE_PUBLIC(BrowserItem)
        public:
		public:
			BrowserItemPrivate(AbstractPropertyBrowser* browser, PropertySheet* property, BrowserItem* parent)
				: m_browser(browser), m_property(property), m_parent(parent), q_ptr(0) {}

			void addChild(BrowserItem* index, BrowserItem* after);
			void removeChild(BrowserItem* index);

			AbstractPropertyBrowser* const m_browser;
			PropertySheet* m_property;
			BrowserItem* m_parent;

			BrowserItem* q_ptr;

			QList<BrowserItem*> m_children;
        };
    }
}
