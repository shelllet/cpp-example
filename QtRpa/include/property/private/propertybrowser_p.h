#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{

        class PropertyBrowserPrivate : public AbstractPropertyBrowserPrivate {
            Q_DECLARE_PUBLIC(PropertyBrowser)
			//	PropertyBrowser* q_ptr;

		public:
			PropertyBrowserPrivate();
			void init(QWidget* parent);

			void propertyInserted(BrowserItem* index, BrowserItem* afterIndex);
			void propertyRemoved(BrowserItem* index);
			void propertyChanged(BrowserItem* index);
			QWidget* createEditor(PropertySheet* property, QWidget* parent)
			{
				Q_Q(PropertyBrowser);
				return q->createEditor(property, parent);
			}
			PropertySheet* indexToProperty(const QModelIndex& index) const;
			QTreeWidgetItem* indexToItem(const QModelIndex& index) const;
			BrowserItem* indexToBrowserItem(const QModelIndex& index) const;
			bool lastColumn(int column) const;
			void disableItem(QTreeWidgetItem* item) const;
			void enableItem(QTreeWidgetItem* item) const;
			bool hasValue(QTreeWidgetItem* item) const;

			void slotCollapsed(const QModelIndex& index);
			void slotExpanded(const QModelIndex& index);

			QColor calculatedBackgroundColor(BrowserItem* item) const;

			PropertyEditorView* treeWidget() const { return m_treeWidget; }
			bool markPropertiesWithoutValue() const { return m_markPropertiesWithoutValue; }

			BrowserItem* currentItem() const;
			void setCurrentItem(BrowserItem* browserItem, bool block);
			void editItem(BrowserItem* browserItem);

			void slotCurrentBrowserItemChanged(BrowserItem* item);
			void slotCurrentTreeItemChanged(QTreeWidgetItem* newItem, QTreeWidgetItem*);

			QTreeWidgetItem* editedItem() const;

		private:
			void updateItem(QTreeWidgetItem* item);

			QMap<BrowserItem*, QTreeWidgetItem*> m_indexToItem;
			QMap<QTreeWidgetItem*, BrowserItem*> m_itemToIndex;

			QMap<BrowserItem*, QColor> m_indexToBackgroundColor;

			PropertyEditorView* m_treeWidget;

			bool m_headerVisible;
			PropertyBrowser::ResizeMode m_resizeMode;
			class PropertyEditorDelegate* m_delegate;
			bool m_markPropertiesWithoutValue;
			bool m_browserChangedBlocked;
			QIcon m_expandIcon;


        };
    }
}

