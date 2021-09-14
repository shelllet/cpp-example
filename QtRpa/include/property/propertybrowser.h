#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
		class BrowserItem;
        class PropertyBrowserPrivate;
        class PropertyBrowser  : public AbstractPropertyBrowser{
            Q_DECLARE_PRIVATE(PropertyBrowser)
			Q_OBJECT
				Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
				Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
				Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
				Q_PROPERTY(bool headerVisible READ isHeaderVisible WRITE setHeaderVisible)
				Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
				Q_PROPERTY(int splitterPosition READ splitterPosition WRITE setSplitterPosition)
				Q_PROPERTY(bool propertiesWithoutValueMarked READ propertiesWithoutValueMarked WRITE setPropertiesWithoutValueMarked)
		public:

            PropertyBrowser(QWidget* parentWidget = 0,Object*parent = nullptr);
			enum ResizeMode
			{
				Interactive,
				Stretch,
				Fixed,
				ResizeToContents
			};
			Q_ENUM(ResizeMode)
			~PropertyBrowser();

			int indentation() const;
			void setIndentation(int i);

			bool rootIsDecorated() const;
			void setRootIsDecorated(bool show);

			bool alternatingRowColors() const;
			void setAlternatingRowColors(bool enable);

			bool isHeaderVisible() const;
			void setHeaderVisible(bool visible);

			ResizeMode resizeMode() const;
			void setResizeMode(ResizeMode mode);

			int splitterPosition() const;
			void setSplitterPosition(int position);

			void setExpanded(BrowserItem* item, bool expanded);
			bool isExpanded(BrowserItem* item) const;

			bool isItemVisible(BrowserItem* item) const;
			void setItemVisible(BrowserItem* item, bool visible);

			void setBackgroundColor(BrowserItem* item, const QColor& color);
			QColor backgroundColor(BrowserItem* item) const;
			QColor calculatedBackgroundColor(BrowserItem* item) const;

			void setPropertiesWithoutValueMarked(bool mark);
			bool propertiesWithoutValueMarked() const;

			void editItem(BrowserItem* item);

	
			signals:

				void collapsed(BrowserItem* item);
				void expanded(BrowserItem* item);

		protected:
			virtual void itemInserted(BrowserItem* item, BrowserItem* afterItem);
			virtual void itemRemoved(BrowserItem* item);
			virtual void itemChanged(BrowserItem* item);

		private:

		//	QScopedPointer<PropertyBrowser> d_ptr;
			//Q_DECLARE_PRIVATE(PropertyBrowser)
			//	Q_DISABLE_COPY_MOVE(PropertyBrowser)

				//Q_PRIVATE_SLOT(d_func(), void slotCollapsed(const QModelIndex&))
				//Q_PRIVATE_SLOT(d_func(), void slotExpanded(const QModelIndex&))
				//Q_PRIVATE_SLOT(d_func(), void slotCurrentBrowserItemChanged(BrowserItem*))
				//Q_PRIVATE_SLOT(d_func(), void slotCurrentTreeItemChanged(QTreeWidgetItem*, QTreeWidgetItem*))
        protected:
            PropertyBrowser(PropertyBrowserPrivate& d, QWidget* parentWidget = 0, Object*parent = nullptr);
        };
    }
}
    