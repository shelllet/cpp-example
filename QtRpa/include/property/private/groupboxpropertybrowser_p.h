#pragma once
namespace shelllet {
    namespace property{
		class BrowserItem;
        class GroupBoxPropertyBrowserPrivate : public AbstractPropertyBrowserPrivate {
            Q_DECLARE_PUBLIC(GroupBoxPropertyBrowser)
        public:
		//	QtGroupBoxPropertyBrowser* q_ptr;
			//Q_DECLARE_PUBLIC(QtGroupBoxPropertyBrowser)
		public:

			void init(QWidget* parent);

			void propertyInserted(BrowserItem* index, BrowserItem* afterIndex);
			void propertyRemoved(BrowserItem* index);
			void propertyChanged(BrowserItem* index);
			QWidget* createEditor(PropertySheet* property, QWidget* parent)
			{
				Q_Q(GroupBoxPropertyBrowser);
				return q->createEditor(property, parent);
			}

			void slotEditorDestroyed();
			void slotUpdate();

			struct WidgetItem
			{
				QWidget* widget{ nullptr }; // can be null
				QLabel* label{ nullptr };
				QLabel* widgetLabel{ nullptr };
				QGroupBox* groupBox{ nullptr };
				QGridLayout* layout{ nullptr };
				QFrame* line{ nullptr };
				WidgetItem* parent{ nullptr };
				QList<WidgetItem*> children;
			};
		private:
			void updateLater();
			void updateItem(WidgetItem* item);
			void insertRow(QGridLayout* layout, int row) const;
			void removeRow(QGridLayout* layout, int row) const;

			bool hasHeader(WidgetItem* item) const;

			QMap<BrowserItem*, WidgetItem*> m_indexToItem;
			QMap<WidgetItem*, BrowserItem*> m_itemToIndex;
			QMap<QWidget*, WidgetItem*> m_widgetToItem;
			QGridLayout* m_mainLayout;
			QList<WidgetItem*> m_children;
			QList<WidgetItem*> m_recreateQueue;
        };
    }
}
