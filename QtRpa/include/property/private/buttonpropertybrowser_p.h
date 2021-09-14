#pragma once
namespace shelllet {
    namespace property{
        class ButtonPropertyBrowserPrivate : public AbstractPropertyBrowserPrivate {
            Q_DECLARE_PUBLIC(ButtonPropertyBrowser)
        public:

			//QtButtonPropertyBrowser* q_ptr;
			//Q_DECLARE_PUBLIC(QtButtonPropertyBrowser)
		public:

			void init(QWidget* parent);

			void propertyInserted(BrowserItem* index, BrowserItem* afterIndex);
			void propertyRemoved(BrowserItem* index);
			void propertyChanged(BrowserItem* index);
			QWidget* createEditor(PropertySheet* property, QWidget* parent)
			{
				Q_Q(ButtonPropertyBrowser);
				return q->createEditor(property, parent);
			}

			void slotEditorDestroyed();
			void slotUpdate();
			void slotToggled(bool checked);

			struct WidgetItem
			{
				QWidget* widget{ nullptr }; // can be null
				QLabel* label{ nullptr }; // main label with property name
				QLabel* widgetLabel{ nullptr }; // label substitute showing the current value if there is no widget
				QToolButton* button{ nullptr }; // expandable button for items with children
				QWidget* container{ nullptr }; // container which is expanded when the button is clicked
				QGridLayout* layout{ nullptr }; // layout in container
				WidgetItem* parent{ nullptr };
				QList<WidgetItem*> children;
				bool expanded{ false };
			};
		private:
			void updateLater();
			void updateItem(WidgetItem* item);
			void insertRow(QGridLayout* layout, int row) const;
			void removeRow(QGridLayout* layout, int row) const;
			int gridRow(WidgetItem* item) const;
			int gridSpan(WidgetItem* item) const;
			void setExpanded(WidgetItem* item, bool expanded);
			QToolButton* createButton(QWidget* panret = 0) const;

			QMap<BrowserItem*, WidgetItem*> m_indexToItem;
			QMap<WidgetItem*, BrowserItem*> m_itemToIndex;
			QMap<QWidget*, WidgetItem*> m_widgetToItem;
			QMap<QObject*, WidgetItem*> m_buttonToItem;
			QGridLayout* m_mainLayout;
			QList<WidgetItem*> m_children;
			QList<WidgetItem*> m_recreateQueue;
        };
    }
}
